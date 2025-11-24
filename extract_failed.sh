#!/bin/bash

# Parsing-Datei für Fehler erstellen
echo "# Failed Tests - Minishell Tester" > failed_mandatory_tests.md
echo "" >> failed_mandatory_tests.md
echo "## 📋 Übersicht" >> failed_mandatory_tests.md
echo "Dieser File enthält alle fehlgeschlagenen Test Cases aus dem mstest Mandatory-Lauf." >> failed_mandatory_tests.md
echo "" >> failed_mandatory_tests.md
echo "**Zusammenfassung:**" >> failed_mandatory_tests.md
echo "- Gesamt Tests: 941" >> failed_mandatory_tests.md
echo "- Erfolgreich: 777" >> failed_mandatory_tests.md
echo "- Fehlgeschlagen: 164" >> failed_mandatory_tests.md
echo "  - STD_OUT Fehler: 84" >> failed_mandatory_tests.md
echo "  - STD_ERR Fehler: 63" >> failed_mandatory_tests.md
echo "  - EXIT_CODE Fehler: 56" >> failed_mandatory_tests.md
echo "" >> failed_mandatory_tests.md

# Funktion zum Extrahieren von Testbefehlen aus einer Datei und Zeilennummer
extract_cmd() {
    local file="$1"
    local line="$2"
    
    # Versuche den Befehl aus der Zeile zu extrahieren
    sed -n "${line}p" "$file" | sed 's/^[[:space:]]*run_test //g' | sed 's/"//g'
}

echo "Verarbeite fehlgeschlagene Tests..."
