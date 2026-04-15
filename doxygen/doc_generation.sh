#!/bin/bash
#
# @file doc_generation.sh — сборка документации Doxygen с подсчётом ошибок и предупреждений
# version: 1.3.0
# date: 2026-02-05
# author: BGM
#
# История изменений:
#   1.3.0 - 2026-02-05: Архитектурная переработка скрипта
#                       Введён main() и пошаговый сценарий выполнения
#                       Логика разбита на изолированные функции
#                       Повышена читаемость и расширяемость
#
#   1.2.0 - 2026-02-05: Транзакционная работа с лог-файлом (backup + rollback)
#                       Добавлен trap ERR для аварийных runtime-ошибок
#                       Разделены классы завершений (127 / 2 / 3)
#                       В CI warnings считаются ошибками
#                       Автооткрытие HTML-документации для локальной диагностики
#
#   1.1.0 - 2025-10-09: Первая версия

set -eEuo pipefail

#region ====================== КОНСТАНТЫ И НАСТРОЙКИ ======================
# Основные параметры
DOXYFILE="Doxyfile"
LOG_FILE="doxygen.log"
LOG_BAK=""
WARNINGS=0
ERRORS=0

# Цвета вывода
RED="\033[0;31m"
YELLOW="\033[1;33m"
GREEN="\033[0;32m"
RESET="\033[0m"
#endregion

#region ====================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ======================
# Восстановление лог-файла из backup в случае ошибки
restore_log_backup() {
    if [ -n "$LOG_BAK" ] && [ -f "$LOG_BAK" ]; then
        mv "$LOG_BAK" "$LOG_FILE"
        echo -e "${YELLOW}⚠  Восстановлен предыдущий лог-файл${RESET}"
    fi
}

# Удаление backup лог-файла
remove_log_backup() {
    if [ -n "$LOG_BAK" ] && [ -f "$LOG_BAK" ]; then
        rm -f "$LOG_BAK"
    fi
}
#endregion

#region ====================== TRAP: АВАРИЙНОЕ ЗАВЕРШЕНИЕ ======================
on_error() {
    restore_log_backup
    echo -e "${RED}❌ Скрипт ${BASH_SOURCE[0]} завершён с ошибкой${RESET}"
    exit 1
}
# trap ERR — страховка от непредусмотренных runtime-ошибок
trap on_error ERR
#endregion

#region ====================== ШАГИ СЦЕНАРИЯ ======================
# Вывод начальной информации
print_start_info() {
    echo "📘 Запуск генерации документации Doxygen..."
    echo "Используется файл конфигурации: ${DOXYFILE}"
}

# Проверка наличия doxygen
check_environment() {
    command -v doxygen >/dev/null 2>&1 || {
        echo -e "${RED}❌ doxygen не найден в PATH${RESET}"
        exit 127
    }
}

# Подготовка рабочей директории
prepare_workdir() {
    local script_dir
    script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    cd "$script_dir"
}

# Подготовка лог-файла
prepare_log() {
    # backup лог-файла если он есть
    if [ -f "$LOG_FILE" ]; then
        LOG_BAK="${LOG_FILE}.bak"
        mv "$LOG_FILE" "$LOG_BAK"
    fi
    # Очистка старого лога
    : > "$LOG_FILE"
}

# Запуск Doxygen
run_doxygen() {
    if ! doxygen "$DOXYFILE" >"$LOG_FILE" 2>&1; then
        echo -e "${RED}❌ Ошибка при выполнении Doxygen${RESET}"
        remove_log_backup
        exit 2
    fi
}

# Подсчёт предупреждений и ошибок
analyze_log() {
    WARNINGS=$(grep -ci "warning:" "$LOG_FILE" || true)
    ERRORS=$(grep -ci "error:" "$LOG_FILE" || true)
}

# Итоговый отчёт
print_report() {
    echo
    echo "📊 РЕЗУЛЬТАТ СБОРКИ:"

    if [ "$ERRORS" -gt 0 ]; then
        echo -e "  ${RED}Ошибок: $ERRORS${RESET}"
    else
        echo -e "  ${GREEN}Ошибок: 0${RESET}"
    fi

    if [ "$WARNINGS" -gt 0 ]; then
        echo -e "  ${YELLOW}Предупреждений: $WARNINGS${RESET}"
    else
        echo -e "  ${GREEN}Предупреждений: 0${RESET}"
    fi

    echo
    echo "📜 Подробный лог: $LOG_FILE"
}

# открытие HTML
open_html() {
    local doc_index="html/index.html"

    if [ -f "$doc_index" ]; then
        printf 'Открываю документацию: %s\n' "$doc_index"
        if [[ "$OSTYPE" == "darwin"* ]]; then
            open "$doc_index" >/dev/null 2>&1 || true
        else
            xdg-open "$doc_index" >/dev/null 2>&1 || true
        fi
    else
        echo -e "${YELLOW}⚠ Документация не сгенерирована (${doc_index} не найден)${RESET}"
    fi
}

# CI exit policy
ci_policy() {
    if [ "$ERRORS" -gt 0 ] || [ "$WARNINGS" -gt 0 ]; then
        exit 3
    fi
}
#endregion

main() {
    print_start_info
    check_environment
    prepare_workdir
    prepare_log
    run_doxygen
    analyze_log
    print_report
    open_html
    remove_log_backup
    ci_policy
}

main "$@"

