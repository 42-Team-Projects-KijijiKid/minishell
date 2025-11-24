# Exit Test Cases - Minishell

## 📋 Übersicht
Dieser File enthält alle Test Cases, die mit dem `exit` Builtin zusammenhängen, inklusive erwarteter Ergebnisse.

---

## Exit Without Arguments

### Test 1: Exit ohne Argumente
```bash
exit
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** Letzter Exit-Status der Shell (normalerweise 0)
**Verhalten:** Minishell terminiert

---

## Exit With Empty String

### Test 2: Exit mit leerem String
```bash
exit ""
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: : numeric argument required
```
**Exit Status:** 2 (oder 255 je nach bash-Version)
**Verhalten:** Shell wird mit Exit-Status 2 beendet

---

## Exit With Multiple Arguments

### Test 3: Exit mit zwei Null-Argumenten
```bash
exit 0 0
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet, nur Fehlermeldung ausgegeben

---

### Test 4: Exit mit zwei String-Argumenten
```bash
exit something somethingv2
```
**Erwartetes Ergebnis:** Fehlermeldung für nicht-numerisches Argument
```
bash: exit: something: numeric argument required
```
**Exit Status:** 2 (oder 255)
**Verhalten:** Shell wird mit Exit-Status 2 beendet

---

### Test 5: Exit mit einem numerischen Argument
```bash
exit 1 2
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet

---

### Test 6: Exit mit drei Argumenten
```bash
exit 1 2 3
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet

---

### Test 7: Exit mit Buchstabe und Zahlen
```bash
exit A 2 3
```
**Erwartetes Ergebnis:** Fehlermeldung für nicht-numerisches Argument
```
bash: exit: A: numeric argument required
```
**Exit Status:** 2 (oder 255)
**Verhalten:** Shell wird mit Exit-Status 2 beendet

---

### Test 8: Exit mit Text-Argument
```bash
exit cd ..
```
**Erwartetes Ergebnis:** Fehlermeldung für nicht-numerisches Argument
```
bash: exit: cd: numeric argument required
```
**Exit Status:** 2 (oder 255)
**Verhalten:** Shell wird mit Exit-Status 2 beendet

---

### Test 9: Exit mit mehreren 42-Argumenten
```bash
exit 42 42 42 42 42
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet

---

### Test 10: Exit mit zwei gleichen Argumenten
```bash
exit 42 42
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet

---

## Exit With String and Number Mix

### Test 11: Exit mit Buchstabe und Zahl (A zuerst)
```bash
exit A 1
```
**Erwartetes Ergebnis:** Fehlermeldung für nicht-numerisches Argument
```
bash: exit: A: numeric argument required
```
**Exit Status:** 2 (oder 255)
**Verhalten:** Shell wird mit Exit-Status 2 beendet

---

### Test 12: Exit mit Zahl und Buchstabe (Zahl zuerst)
```bash
exit 1 A
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet

---

## Exit With Positive Numbers

### Test 13: Exit mit +100 in Quotes
```bash
exit "+100"
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** 100
**Verhalten:** Shell terminiert mit Exit-Status 100

---

### Test 14: Exit mit +1
```bash
exit +1
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** 1
**Verhalten:** Shell terminiert mit Exit-Status 1

---

## Exit With Negative Numbers

### Test 15: Exit mit -100 in Quotes
```bash
exit "-100"
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** 156 (256 - 100 = 156, da Exit-Status modulo 256 berechnet wird)
**Hinweis:** Negative Zahlen werden als (256 + (n % 256)) berechnet
**Verhalten:** Shell terminiert mit Exit-Status 156

---

### Test 16: Exit mit -1
```bash
exit -1
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** 255 (256 - 1 = 255)
**Verhalten:** Shell terminiert mit Exit-Status 255

---

### Test 17: Exit mit großer negativer Zahl
```bash
exit -12560
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** Berechnung: -12560 % 256 = -16, dann 256 + (-16) = 240
**Exit Status:** 240
**Verhalten:** Shell terminiert mit Exit-Status 240

---

### Test 18: Exit mit sehr großer negativer Zahl (out of range)
```bash
exit -9223372036854775805
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** Berechnung durch Modulo 256
**Hinweis:** -9223372036854775805 % 256 = -253, dann 256 + (-253) = 3
**Exit Status:** 3
**Verhalten:** Shell terminiert mit Exit-Status 3

---

## Exit Status Testing with Commands

### Test 19: Exit-Status von fehlgeschlagenem Befehl
```bash
/bin/cat 42
echo $?
```
**Erwartetes Ergebnis:**
```
/bin/cat: 42: No such file or directory
1
```
**Exit Status von cat:** 1
**Hinweis:** Testet, ob $? korrekt gesetzt wird

---

### Test 20: Exit-Status von erfolgreichem Befehl zweimal verwendet
```bash
/bin/echo 42
expr $? + $?
```
**Erwartetes Ergebnis:**
```
42
0
```
**Hinweis:** Erstes $? ist 0 (von echo), zweites $? ist auch 0 (da echo erfolgreich war)
**Ergebnis von expr:** 0

---

### Test 21: Exit-Status von fehlgeschlagenem Befehl in expr
```bash
/bin/cat 42
expr $? + $?
```
**Erwartetes Ergebnis:**
```
/bin/cat: 42: No such file or directory
2
```
**Hinweis:** $? ist 1 (von cat), expr rechnet 1 + 1 = 2
**Exit Status von expr:** 0 (expr selbst war erfolgreich)

---

## Exit Modulo 256 Behavior

### Hinweis: Exit-Status wird immer modulo 256 berechnet

**Beispiele:**
- `exit 0` → Exit-Status: 0
- `exit 1` → Exit-Status: 1
- `exit 255` → Exit-Status: 255
- `exit 256` → Exit-Status: 0 (256 % 256)
- `exit 257` → Exit-Status: 1 (257 % 256)
- `exit 300` → Exit-Status: 44 (300 % 256)
- `exit 1000` → Exit-Status: 232 (1000 % 256)
- `exit -1` → Exit-Status: 255
- `exit -2` → Exit-Status: 254
- `exit -256` → Exit-Status: 0
- `exit -257` → Exit-Status: 255

---

## Edge Cases Summary

### Wichtige Regeln für Exit:

1. **Ohne Argumente:** Beendet Shell mit letztem Exit-Status
2. **Mit einem numerischen Argument:** Beendet Shell mit diesem Status (modulo 256)
3. **Mit mehreren Argumenten:** Fehlermeldung "too many arguments", Shell wird NICHT beendet, Exit-Status 1
4. **Mit nicht-numerischem Argument:** Fehlermeldung "numeric argument required", Shell wird beendet mit Exit-Status 2 (oder 255)
5. **Mit leerem String:** Wie nicht-numerisches Argument
6. **Positive Zahlen mit +:** Akzeptiert (z.B. +100 → 100)
7. **Negative Zahlen:** Werden modulo 256 berechnet und dann von 256 subtrahiert
8. **Sehr große Zahlen:** Werden modulo 256 berechnet

---

## Special Cases

### Test 22: Exit nach mehreren echo -n Befehlen
```bash
echo -n -n -n 42
exit
```
**Erwartetes Ergebnis:** 
```
42
```
Shell wird mit letztem Exit-Status beendet (0, da echo erfolgreich war)

---

### Test 23: Exit nach mehreren echo Befehlen
```bash
echo -n -n -n -n 42
exit
```
**Erwartetes Ergebnis:** 
```
42
```
Shell wird mit Exit-Status 0 beendet

---

## Test-Szenarien für Debugging

### Szenario 1: Exit-Status Chain
```bash
/bin/cat 42
echo $?
```
**Erwartung:** `1` wird ausgegeben (Fehler-Status von cat)

---

### Szenario 2: Exit mit mehreren Argumenten stoppt nicht
```bash
exit 1 2 3
echo "Still alive"
```
**Erwartung:** 
```
bash: exit: too many arguments
Still alive
```
Shell läuft weiter!

---

### Szenario 3: Exit mit ungültigem Argument stoppt Shell
```bash
exit ABC
echo "Never reached"
```
**Erwartung:** 
```
bash: exit: ABC: numeric argument required
```
Shell wird beendet, "Never reached" wird NICHT ausgegeben

---

## Summary

**Gesamt Test Cases:** 23+

**Kategorien:**
- Exit Without Arguments: 1 Test
- Exit With Empty String: 1 Test
- Exit With Multiple Arguments: 10 Tests
- Exit With String and Number Mix: 2 Tests
- Exit With Positive Numbers: 2 Tests
- Exit With Negative Numbers: 4 Tests
- Exit Status Testing: 3 Tests
- Special Cases: 2 Tests

**Wichtigste Testpunkte:**
1. ✅ Exit ohne Argumente
2. ✅ Exit mit einem numerischen Argument
3. ✅ Exit mit mehreren Argumenten (sollte Fehler geben, Shell NICHT beenden)
4. ✅ Exit mit nicht-numerischen Argumenten (sollte Shell beenden mit Status 2)
5. ✅ Exit mit leeren Strings
6. ✅ Modulo 256 Berechnung für Exit-Status
7. ✅ Negative Zahlen korrekt behandeln
8. ✅ Sehr große Zahlen (overflow)
9. ✅ Positive Zahlen mit + Prefix
10. ✅ Exit-Status-Verkettung mit $?

**Häufigste Fehlerquellen:**
1. Mehrere Argumente: Shell wird NICHT beendet (Exit-Status 1)
2. Nicht-numerische Argumente: Shell WIRD beendet (Exit-Status 2)
3. Modulo 256 Berechnung bei großen Zahlen
4. Negative Zahlen richtig umrechnen
5. Leerer String wird als nicht-numerisch behandelt









exit 0 0

exit

exit ""

exit 1 2

exit 1 2 3

exit 42 42 42 42 42 






exit something somethingv2

exit

exit ""

exit A 2 3

exit cd ..














  # **************************************************************************** #
  #                                PARSING HELL                                  #
  # **************************************************************************** #
  1:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:5  
  2:    STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:7  
  3:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:10  
  4:    STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:14  
  5:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:18  
  6:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:20  
  7:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:22  
  8:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:24  
  9:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:26  
  10:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:28  
  11:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:30  
  12:   STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(130)  bash(0) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:32  
  13:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:37  
  14:   STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(130)  bash(0) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:40  
  15:   STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(130)  bash(0) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:45  
  16:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:52  
  17:   STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:54  
  18:   STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:58  
  19:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:62  
  20:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:66  
  21:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:69  
  22:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:72  
  23:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:75  
  24:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:78  
  25:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:81  
  26:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:84  
  27:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:87  
  28:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:90  
  29:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:93  
  30:   STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:96  
  31:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:99  
  32:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:102  
  33:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:104  
  34:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:106  
  35:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:108  
  36:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:110  
  37:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:112  
  38:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:114  
  39:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:116  
  40:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:118  
  41:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:120  
  42:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:123  
  43:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:126  
  44:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:129  
  45:   /home/aeckert/42_minishell_tester/tester.sh: line 217: 378582 Done                    echo -n "$INPUT"
     378583 Segmentation fault      (core dumped) | $MINISHELL_PATH/$EXECUTABLE 2> tmp_err_minishell > tmp_out_minishell
STD_OUT: ❌  STD_ERR: ❌  EXIT_CODE: ❌ [ minishell(139)  bash(0) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:132  
  46:   /home/aeckert/42_minishell_tester/tester.sh: line 217: 378594 Done                    echo -n "$INPUT"
     378595 Segmentation fault      (core dumped) | $MINISHELL_PATH/$EXECUTABLE 2> tmp_err_minishell > tmp_out_minishell
STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(139)  bash(127) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:135  
  47:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:138  
  48:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:141  
  49:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:144  
  50:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:147  
  51:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:150  
  52:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:153  
  53:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:156  
  54:   /home/aeckert/42_minishell_tester/tester.sh: line 217: 378648 Done                    echo -n "$INPUT"
     378649 Segmentation fault      (core dumped) | $MINISHELL_PATH/$EXECUTABLE 2> tmp_err_minishell > tmp_out_minishell
STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ❌ [ minishell(139)  bash(0) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:159  
  55:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:161  
  56:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:164  
  57:   /home/aeckert/42_minishell_tester/tester.sh: line 217: 378672 Done                    echo -n "$INPUT"
     378673 Segmentation fault      (core dumped) | $MINISHELL_PATH/$EXECUTABLE 2> tmp_err_minishell > tmp_out_minishell
STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ❌ [ minishell(139)  bash(0) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:167  
  58:   STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:170  
  59:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:173  
  60:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:175  
  61:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:177  
  62:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:179  
  63:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:181  
  64:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:183  
  65:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:185  
  66:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:187  
  67:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:189  
  68:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:191  
  69:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:193  
  70:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:195  
  71:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:198  
  72:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:201  
  73:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:204  
  74:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:207  
  75:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:210  
  76:   /home/aeckert/42_minishell_tester/tester.sh: line 217: 378796 Done                    echo -n "$INPUT"
     378797 Segmentation fault      (core dumped) | $MINISHELL_PATH/$EXECUTABLE 2> tmp_err_minishell > tmp_out_minishell
STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(139)  bash(127) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:213  
  77:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:216  
  78:   STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:219  
  79:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:222  
  80:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:225  
  81:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:227  
  82:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:229  
  83:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:231  
  84:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:233  
  85:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:236  
  86:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:239  
  87:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:242  
  88:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:244  
  89:   /home/aeckert/42_minishell_tester/tester.sh: line 217: 378881 Done                    echo -n "$INPUT"
     378882 Segmentation fault      (core dumped) | $MINISHELL_PATH/$EXECUTABLE 2> tmp_err_minishell > tmp_out_minishell
STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(139)  bash(127) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:247  
  90:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:250  
  91:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:252  
  92:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:254  
  93:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:256  
  94:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:258  
  95:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:260  
  96:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:262  
  97:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:264  
  98:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:266  
  99:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:268  
  100:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:270  
  101:  STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:272  
  102:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:274  
  103:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:276  
  104:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:278  
  105:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:280  
  106:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:282  
  107:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:284  
  108:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:286  
  109:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:288  
  110:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:290  
  111:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:293  
  112:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:297  
  113:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:299  
  114:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:301  
  115:  STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:303  
  116:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:305  
  117:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:307  
  118:  STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:309  
  119:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:311  
  120:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:313  
  121:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:315  
  122:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:317  
  123:  STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(2)  bash(127) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:319  
  124:  STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ❌ [ minishell(1)  bash(0) ]  /home/aeckert/42_minishell_tester/cmds/mand/10_parsing_hell.sh:321  

   # **************************************************************************** #
  #                                COMPARE PARSING                               #
  # **************************************************************************** #
  1:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:6  
  2:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:8  
  3:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:10  
  4:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:12  
  5:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:14  
  6:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:16  
  7:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:18  
  8:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:20  
  9:    STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:22  
  10:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:24  
  11:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:26  
  12:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:28  
  13:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:30  
  14:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:32  
  15:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:34  
  16:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:36  
  17:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:38  
  18:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:40  
  19:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:42  
  20:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:44  
  21:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:46  
  22:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:48  
  23:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:50  
  24:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:52  
  25:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:54  
  26:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:56  
  27:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:58  
  28:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:60  
  29:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:62  
  30:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:64  
  31:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:66  
  32:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:68  
  33:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:70  
  34:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:72  
  35:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:74  
  36:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:76  
  37:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:78  
  38:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:80  
  39:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:82  
  40:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:84  
  41:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:86  
  42:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:88  
  43:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:90  
  44:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:92  
  45:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:94  
  46:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:96  
  47:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:98  
  48:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:100  
  49:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:102  
  50:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:104  
  51:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:106  
  52:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:108  
  53:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:110  
  54:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:112  
  55:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:114  
  56:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:116  
  57:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:118  
  58:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:120  
  59:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:122  
  60:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:124  
  61:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:126  
  62:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:128  
  63:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:130  
  64:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:132  
  65:   STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:134  
  66:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:136  
  67:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:138  
  68:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:140  
  69:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:142  
  70:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:144  
  71:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:146  
  72:   STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:148  
  73:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:150  
  74:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:152  
  75:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:154  
  76:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:156  
  77:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:158  
  78:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:160  
  79:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:162  
  80:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:164  
  81:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:166  
  82:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:168  
  83:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:170  
  84:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:172  
  85:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:174  
  86:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:176  
  87:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:178  
  88:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:180  
  89:   STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  /home/aeckert/42_minishell_tester/cmds/mand/0_compare_parsing.sh:182 









>> '$USER'
cat '$USER'
/bin/rm -f '$USER'