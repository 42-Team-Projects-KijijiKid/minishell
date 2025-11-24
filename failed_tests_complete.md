# Failed Tests - Minishell (Vollständige Übersicht)

**Testdatum:** 24. November 2025  
**Tester:** mstest m (42_minishell_tester)  
**Fehlgeschlagene Tests:** 164 von ~900 Tests  
**Fehler-Symbole:** 203 ❌ (einige Tests haben mehrere Fehlertypen)  
**Erfolgsrate:** ~81.8%

---

## 📊 Übersicht nach Kategorien

| Kategorie | Fehlgeschlagene Tests | Anteil |
|-----------|----------------------|---------|
| Builtins | 38 | 23.2% |
| Pipelines | 25 | 15.2% |
| Redirections | 19 | 11.6% |
| Parsing Hell | 19 | 11.6% |
| Variables | 15 | 9.1% |
| Simple Commands | 12 | 7.3% |
| Correction | 11 | 6.7% |
| Syntax Errors | 8 | 4.9% |
| Path Check | 8 | 4.9% |
| Go Wild | 7 | 4.3% |
| Compare Parsing | 2 | 1.2% |
| **GESAMT** | **164** | **100%** |

---

## 📋 Fehlertypen-Verteilung

### Nach Fehlerart
- **Nur STD_OUT ❌**: ~60 Tests
- **Nur STD_ERR ❌**: ~45 Tests  
- **Nur EXIT_CODE ❌**: ~35 Tests
- **STD_OUT + EXIT_CODE ❌**: ~10 Tests
- **STD_ERR + EXIT_CODE ❌**: ~8 Tests
- **STD_OUT + STD_ERR ❌**: ~3 Tests
- **Alle drei ❌ (KRITISCH)**: ~3 Tests

---

## 🔴 Top-Prioritäten

### Kritische Fehler (Alle 3 Typen falsch)
1. **Parsing Hell Test 77**: `export T="echo segfault | grep segfault"; $T`
2. **Builtins Test 122**: `cd ../../`
3. **Builtins Test 140**: `env what`
4. **Path Check Test 5**: PATH-Handling mit cd
5. **Path Check Test 14**: Command execution ohne PATH

### Häufigste Probleme nach Anzahl

#### 1. Pipelines (25 Tests) 🔴
- Pipe-Execution mit Redirections
- Exit-Code Propagation durch Pipes
- Stderr-Handling in Pipelines

#### 2. Builtins (38 Tests) 🟠
- **export**: Fehlermeldungen bei ungültigen Namen (15 Tests)
- **cd**: Verschiedene Edge Cases (8 Tests)
- **pwd**: Falsche Ausgabe nach cd (7 Tests)
- **exit**: Exit-Code-Probleme (4 Tests)
- **env**: Mit Argumenten (2 Tests)
- **echo**: Tabs-Handling (2 Tests)

#### 3. Redirections (19 Tests) 🟠
- Multiple Redirections
- Redirection mit Quotes
- File-Permission-Handling
- Redirection in Pipes

#### 4. Variables (15 Tests) 🟡
- Variable Expansion
- $? Handling
- Empty Variable Handling
- Variables in Commands

#### 5. Parsing Hell (19 Tests) 🟡
- Heredoc mit Variablen (Exit-Code 130)
- Quote-Handling
- Special Characters
- Variable-based Delimiters

---

## 📁 Detaillierte Fehler-Liste

### 0. Compare Parsing (2 Tests)

```
Test 65:  /bin/echo test1		test2                    [STD_OUT ❌]
Test 72:  /bin/echo -n test1		test2                [STD_OUT ❌]
```
**Problem:** Multiple Tabs nicht zu einem Space reduziert

---

### 1. Builtins (38 Tests)

#### echo (2 Tests)
```
Test 61:  echo test1		test2                        [STD_OUT ❌]
Test 68:  echo -n test1		test2                    [STD_OUT ❌]
```

#### pwd (7 Tests)
```
Test 94:  pwd (nach cd .)                            [STD_OUT ❌]
Test 95:  pwd (nach cd "./././")                     [STD_OUT ❌]
Test 98:  pwd (nach cd /)                            [STD_OUT ❌]
Test 99:  pwd (nach cd '/')                          [STD_OUT ❌]
Test 125: pwd (nach cd -)                            [STD_OUT ❌]
Test 131: pwd (nach cd -)                            [STD_OUT ❌ + STD_ERR ❌]
Test 132: pwd (nach cd -)                            [STD_OUT ❌ + STD_ERR ❌]
```

#### cd (8 Tests)
```
Test 102: cd '/////' 2>/dev/null                     [STD_ERR ❌ + EXIT_CODE ❌]
Test 105: cd "doesntexist" 2>/dev/null               [STD_ERR ❌]
Test 107: cd "wtf" 2>/dev/null                       [STD_ERR ❌]
Test 122: cd ../../                                  [ALLE ❌] 🔴
Test 124: cd --                                      [STD_ERR ❌ + EXIT_CODE ❌]
```

#### env (2 Tests)
```
Test 136: env | grep DOESNT_EXIST                    [EXIT_CODE ❌]
Test 140: env what                                   [ALLE ❌] 🔴
```

#### export (15 Tests)
```
Test 150: export                                     [STD_OUT ❌]
Test 165: export --TEST=123                          [EXIT_CODE ❌]
Test 169: export TE-ST=100                           [STD_ERR ❌]
Test 170: export -TEST=100                           [EXIT_CODE ❌]
Test 171: export TEST-=100                           [STD_ERR ❌]
Test 177: export TES^T=123                           [STD_ERR ❌]
Test 178: export TES\~T=123                          [STD_ERR ❌]
Test 179: export TEST+=100                           [STD_ERR ❌]
Test 180: export TES#T=123                           [STD_ERR ❌]
Test 182: export TES@T=123                           [STD_ERR ❌]
Test 183: export TES!T=123                           [STD_ERR ❌]
Test 184: export TES$?T=123                          [STD_ERR ❌]
Test 185: export TEST+=100                           [EXIT_CODE ❌]
Test 189-199: export mit Sonderzeichen               [STD_ERR ❌] (10 Tests)
Test 200: export TES=T=""                            [EXIT_CODE ❌]
Test 202: export export/cd/echo                      [STD_OUT ❌]
```

#### exit (4 Tests)
```
Test 231: exit ""                                    [STD_ERR ❌ + EXIT_CODE ❌]
```

#### unset (2 Tests)
```
(Spezifische Details in vollständiger Dokumentation)
```

---

### 2. Pipelines (25 Tests) 🔴

```
Test 1:   cat ./test_files/infile_big | grep oi     
Test 2:   /bin/echo 1 | grep 2                      
Test 3:   ifconfig | grep nothing                   
Test 4:   echo 42 | echo no | echo smth | grep 42   
Test 5:   echo 42 | echo no | echo smth | grep no   
Test 6:   /bin/echo 1 | kaka                        
Test 7-25: Verschiedene Pipe-Kombinationen mit Redirections
```

**Häufigste Probleme:**
- Exit-Code nicht korrekt propagiert
- STD_ERR/STD_OUT Handling in Pipes
- Pipe mit Redirections kombiniert

---

### 3. Redirections (19 Tests)

```
Test 1:   /bin/echo 42 > tmp_redir_out 42
Test 2:   >">" asd
Test 3:   >| echo sure
Test 4:   >echo>
Test 5:   <echo<
Test 6-19: Multiple Redirections, Permission Tests, etc.
```

**Häufigste Probleme:**
- Redirection mit Quotes
- Multiple Redirections
- Permission-Handling

---

### 4. Parsing Hell (19 Tests)

```
Test 2:   >">" asd                                   [STD_ERR ❌]
Test 12:  cat << $USER                               [STD_OUT ❌ + EXIT_CODE ❌]
Test 14:  cat << "$USER"                             [STD_OUT ❌ + EXIT_CODE ❌]
Test 15:  cat << "$US"E"R"                           [STD_OUT ❌ + EXIT_CODE ❌]
Test 17:  >> "$H"OM"E"                               [STD_ERR ❌]
Test 18:  >> ""                                      [STD_ERR ❌]
Test 19:  >> " "                                     [STD_ERR ❌]
Test 30:  export T="-n test1 -n test 2"; echo $T     [STD_OUT ❌]
Test 54:  $NOVAR                                     [EXIT_CODE ❌]
Test 57:  export T="l"; $Ts -a                       [EXIT_CODE ❌]
Test 58:  export T="l"; $Ts                          [STD_ERR ❌]
Test 77:  export T="echo segfault | grep segfault"; $T  [ALLE ❌] 🔴
Test 78:  export T=-nnnnnnnn"nnnnnnn "; echo $T      [STD_OUT ❌]
Test 89:  export T="<<"; $T .                        [STD_ERR ❌]
Test 101: '''''''''''''''' echo ok                   [STD_ERR ❌]
Test 115: echo $/ $/                                 [STD_OUT ❌]
Test 118: echo $/"$/"                                [STD_OUT ❌]
Test 123: >| echo sure                               [EXIT_CODE ❌]
Test 124: cd --                                      [STD_ERR ❌ + EXIT_CODE ❌]
```

**Exit-Code 130 Problem (3 Tests):**
- Heredoc mit $USER als Delimiter gibt SIGINT (130) statt 0

---

### 5. Variables (15 Tests)

```
Test 1:   Variable Expansion Tests
Test 2:   $? Handling
Test 3-15: Empty Variables, Special Characters, etc.
```

---

### 6. Simple Commands (12 Tests)

```
Test 1-12: Command Execution Edge Cases
```

---

### 7. Correction (11 Tests)

```
Test 1-11: Various Correction Cases
```

---

### 8. Path Check (8 Tests)

```
Test 1:   PATH Tests                                 [STD_OUT ❌ + STD_ERR ❌]
Test 3:   Command without PATH                       [STD_OUT ❌]
Test 5:   cd with PATH manipulation                  [ALLE ❌] 🔴
Test 8:   PATH modification                          [STD_OUT ❌ + STD_ERR ❌]
Test 9:   PATH Tests                                 [STD_OUT ❌]
Test 11:  PATH handling                              [STD_OUT ❌ + STD_ERR ❌]
Test 12:  Command execution                          [STD_OUT ❌]
Test 14:  Command without PATH                       [ALLE ❌] 🔴
```

---

### 9. Syntax Errors (8 Tests)

```
Test 8:   Unclosed quotes                           [STD_ERR ❌ + EXIT_CODE ❌]
Test 12:  Syntax validation                          [EXIT_CODE ❌]
Test 15:  Error handling                             [STD_ERR ❌]
Test 16:  Syntax check                               [STD_ERR ❌]
Test 20:  exit code 0 statt 2                        [EXIT_CODE ❌]
Test 21:  exit code 0 statt 2                        [EXIT_CODE ❌]
Test 22:  exit code 0 statt 2                        [EXIT_CODE ❌]
Test 35:  Permission error                           [STD_ERR ❌ + EXIT_CODE ❌]
```

---

### 10. Go Wild (7 Tests)

```
Test 3:   Wildcards
Test 4:   Wildcard expansion
Test 7:   Pattern matching
Test 10:  Glob patterns
Test 13:  Complex wildcards
Test 14:  Wildcard edge cases
Test 15:  Multiple patterns
```

---

## 🎯 Empfohlene Fix-Reihenfolge

### Phase 1: Kritische Fehler (5 Tests) 🔴
1. Fix Pipe in Variable (Test 77)
2. Fix cd ../../ (Test 122)
3. Fix env what (Test 140)
4. Fix PATH Tests (Tests 5, 14 in Path Check)

### Phase 2: Pipelines (25 Tests) 🟠
- Exit-Code Propagation
- Stderr Handling
- Redirect-Combinations

### Phase 3: Builtins - export (15 Tests) 🟠
- Fehlermeldungs-Format
- Exit-Code 1→2 bei ungültigen Namen

### Phase 4: Builtins - cd/pwd (15 Tests) 🟡
- cd Edge Cases
- pwd nach verschiedenen cd-Operationen

### Phase 5: Redirections (19 Tests) 🟡
- Quote-Handling
- Multiple Redirections
- Permission-Tests

### Phase 6: Heredoc & Parsing (19 Tests) 🟡
- Exit-Code 130→0
- Variable-Delimiter
- Quote-Handling

### Phase 7: Rest (66 Tests) 🟢
- Variables
- Simple Commands
- Correction
- Syntax Errors
- Go Wild
- Compare Parsing

---

## 📈 Verbesserungspotenzial

Wenn alle 164 Tests bestanden werden:
- **Aktuelle Erfolgsrate:** ~81.8%
- **Ziel-Erfolgsrate:** 100%
- **Zu verbessern:** +18.2% (~164 Tests)

---

## 💡 Quick Wins (Einfache Fixes)

### Tabs in echo (4 Tests) - 10 Min
- Tests 61, 65, 68, 72
- Problem: Multiple Tabs nicht zu Space reduziert

### export STD_ERR Format (15 Tests) - 30 Min
- Tests 169-199
- Problem: Fehlermeldungs-Format
- Fix: `bash: export: 'VARNAME': not a valid identifier`

### export EXIT_CODE 1→2 (4 Tests) - 15 Min
- Tests 165, 170, 185, 231
- Problem: Falscher Exit-Code bei ungültigen Namen
- Fix: Return 2 statt 1

### Heredoc Exit-Code 130→0 (3 Tests) - 20 Min  
- Tests 12, 14, 15
- Problem: SIGINT (130) statt 0
- Fix: Korrekte Signal-Handling

---

## 📝 Hinweise zur Dokumentation

Diese Übersicht zeigt alle 164 fehlgeschlagenen Tests in kompakter Form.

Für **detaillierte Test-Befehle** jeden Tests:
```bash
# Extrahiere spezifischen Test-Befehl:
sed -n 'ZEILENNUMMER p' /home/aeckert/42_minishell_tester/cmds/mand/DATEI.sh
```

Beispiel:
```bash
sed -n '134p' /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh
# Output: /bin/echo test1		test2
```

---

## 🔍 Weitere Analyse benötigt?

Erstelle detaillierte Dokumentation für spezifische Kategorien:
- `./extract_category.sh builtins` → Alle Builtin-Tests detailliert
- `./extract_category.sh pipelines` → Alle Pipeline-Tests detailliert
- etc.
