

























# Failed Tests - Minishell

## 📋 Inhaltsverzeichnis
- [ECHO Builtin](#echo-builtin)
- [CD Builtin](#cd-builtin)
- [PWD Builtin](#pwd-builtin)
- [EXPORT Builtin](#export-builtin)
- [UNSET Builtin](#unset-builtin)
- [ENV Builtin](#env-builtin)
- [EXIT Builtin](#exit-builtin)
- [Variable Expansion](#variable-expansion)
- [Quoting & Escaping](#quoting--escaping)
- [Pipes](#pipes)
- [Redirections](#redirections)
- [Heredoc](#heredoc)
- [PATH Handling](#path-handling)
- [Command Execution](#command-execution)
- [Edge Cases & Special Cases](#edge-cases--special-cases)

---

## ECHO Builtin

### Basic Echo Tests
```bash
echo
echo 1
echo "  "Hello "World "
echo '  ' Hello World
echo '  'Hello 'World '
echo " "" " ' ' " " ' ' " "
```

### Echo with -n Flag
```bash
echo -n 42
echo -n 42 -n
echo -n -n -n 42
echo -n -n -n -n 42
echo -n test1
echo -n "test1 test2"
echo -n "test1 test2" test3
echo -n " test1 test2 " 'test3 '
echo -n test1		test2
echo -n -n test1
echo -n -n -n -n -n test1
echo -n -n -nasd
echo -n -n -n-nnnnn
echo -n -nnnnnnn -n -nnn -nnnnn -n-n
echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain
echo -n -n -n-n
echo -nnnnnnnnnnnn
```

### Echo with Tabs
```bash
echo test1		test2
/bin/echo test1		test2
/bin/echo -n test1		test2minishell/failed_tests.md
```

### Echo with Variable-Based Flags
```bash
export T=n
echo "-"$T$T

export T=-nnnnnnnn"nnnnnnn "
echo $T

export T=-"n                    "
Echo $T

export T="-n test1 -n test 2"
echo $T

export T=nnnnnnnn
echo "-""$T"nnnnnnnnnnnnn -nnnnnnnn"$T" '-'"$T"

export T=nnnnnnnn
echo "-""$T"nnnnnnnnnnnnn -nnnnnnnn"$T" '-''$T'

export T=nnnnnnnn
echo "-"'$T'nnnnnnnnnnnnn -nnnnnnnn'$T' '-'"$T "

export T=nnnnnnnn
echo "-"'$T'nnnnnnnnnnnnn -nnnnnnnn$T '-''$T '
```

### Echo via Variables (Command Construction)
```bash
export T=ech
echo $To

export T=ech
echo $T"o"

export T=ech
echo $T"o "

export T=ech
echo $T"o -n"

export T=ech
echo $T'o'

export T=ech
echo $T'o '

export T=e E=c S=h L=o
$T$E$S$L

export T=e E=c S=h L=o L=ok
$T$E$S$L

export T=e E=c S=h L=o
$T$E$S$L -n

export T=E E=c S=h L=o
$T$E$S$L -n

export T=E E=c S=h L=o
$T$E$S$L -nn

export T=e E=c S=h L=o
$T$E$S$L -nn

export T=e E=c S=h L=o
$T$E"c"$L -nn

export T=e E=c S=h L=o
$T$E"C"$L -nn

export T=e E=c S=h L=o
$T$E"C"$L "" -""n
```

---

## CD Builtin

### Basic CD Tests
```bash
pwd
cd .
pwd

pwd
cd "."
pwd

pwd
cd ./././
pwd

pwd
cd /
pwd

cd '/////' 2>/dev/null

cd "doesntexist" 2>/dev/null 

cd "wtf" 2>/dev/null 

pwd
cd '/'
pwd

cd ~/Desktop/
pwd
```

### CD with OLDPWD (cd -)
```bash
cd ../../
cd -
cd -

pwd
cd ~
cd -
pwd

pwd
cd -
pwd

cd -
```

### CD with Invalid Options
```bash
cd --
```

### CD in Pipes
```bash
pwd
ls|cat Makefile|>> out|cd ..
/bin/rm -f out
pwd

pwd
cd .. |ls|cat Makefile|>> out
pwd
/bin/rm -f out
```

### CD without PATH
```bash
unset PATH
cd /bin
ls

unset PATH
cd /bin/../bin/
ls

unset PATH
cd /bin/../bin/../bin/../bin/../bin/../bin/../bin/../bin/
../bin/../bin/ls

unset PATH
cd /bin/
sleep 2

unset PATH
echo $PATH
/bin/ls
echo 1
cd -
echo 42
```

---

## PWD Builtin

```bash
pwd
cd .
pwd

pwd
cd "."
pwd

pwd
cd ./././
pwd

pwd
cd /
pwd

pwd
cd '/'
pwd

pwd
cd ~
cd -
pwd

pwd
cd -
pwd

cd ~/Desktop/
pwd

unset PATH
pwd
```

---

## EXPORT Builtin

### Basic Export Tests
```bash
export

export export

export echo

export cd

export test

export TEST

export TEST=

export TEST=123

export ___TEST=123

export _TEST=100

export TES_T=123

export TEST_=123

export ________=123

export TEST=100
```

### Export with Multiple Variables
```bash
export a="asd"

export a="asd" b="de" o= c="hellomi" X

export miert ne lehetne ezt is
```

### Export - Variable Overwriting
```bash
export L=amazing L=ok L=cool
echo $L

export L=amazing L=ok L=cool
export L=ok
echo $L

export T=a T=b T=c
echo $T
```

### Export - Invalid Variable Names
```bash
export --TEST=123

export TE-ST=100

export -TEST=100

export TEST-=100

export TES=T=""

export TE+S=T=""

export TES.T=123

export TES+T=123

export TES=T=123

export TES}T=123

export TES{T=123

export TES-T=123

export TE*ST=123

export TES#T=123

export TES@T=123

export TES!T=123

export TES$?T=123

export TES^T=123

export TES\~T=123

export TEST+=100
```

### Export - Special Values
```bash
/bin/echo $HALLO42
env | grep HALLO42
export HALLO42=42minishell/failed_tests.md
/bin/echo $HALLO42
env | grep HALLO42

/bin/echo $HOME
env | grep HOME
export HOME=42
/bin/echo $HOME
env | grep HOME

export TES_T=123
/bin/echo $TES_T
env | grep TES_T

export HELLO42=T=""
/bin/echo $HELLO42
env | grep HELLO42
env | grep HELLO42=T=

/bin/echo $mini_test
env | grep mini_test
export mini_test=
/bin/echo $mini_test
env | grep mini_test

export USER=
env | grep USER

export USER="@?/"
env | grep USER

export NEW="4 2"
env | grep NEW

export NEW="4=2"
env | grep NEW

export NEW=4=2
env | grep 4=2
```

### Export in Pipes
```bash
export GHOST=123 | env | grep GHOST
```

### Export with Special Syntax
```bash
"e"'x''p''o''r''t' L=T
echo $T
```

---

## UNSET Builtin

### Basic Unset Tests
```bash
export a="asd"
unset a

export a="asd" b="de" o= c="hellomi" X
unset o

export a="asd" b="de" o= c="hellomi" X
unset X

export a="asd" b="de" o= c="hellomi" X
unset o a X b c

export a="asd" b="de" o= c="hellomi" X
unset o asd B x X wqd c

export NEW=42
env | grep NEW
unset NEW
env | grep NEW
unset NEW
unset NEW
unset NEW
unset NEW
unset NEW
env | grep NEW
```

### Unset - Invalid Syntax
```bash
unset TES;T

unset -TEST
```

### Unset PATH
```bash
unset PATH
pwd

unset PATH
cd /bin
ls

unset PATH
cd /bin/../bin/
ls

unset PATH
cd /bin/../bin/../bin/../bin/../bin/../bin/../bin/../bin/
../bin/../bin/ls

unset PATH
cd /bin/
sleep 2

unset PATH
echo $PATH
/bin/ls
echo 1
cd -
echo 42
```

---

## ENV Builtin

### Basic Env Tests
```bash
env | grep DOESNT_EXIST

env what

/bin/env | grep "_="
```

### Env with Export
```bash
export USER=
env | grep USER

export USER="@?/"
env | grep USER

export NEW="4 2"
env | grep NEW

export NEW="4=2"
env | grep NEW

export NEW=4=2
env | grep 4=2
```

### Env in Complex Contexts
```bash
echo "env | /usr/bin/wc -l" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

env -i ./minishell
cd /bin/
ls
```

---

## EXIT Builtin

### Exit with Arguments
```bash
exit

exit ""

exit 0 0

exit something somethingv2

exit "+100"

exit "-100"

exit -9223372036854775805

exit +1

exit -1

exit -12560

exit 1 2

exit 1 2 3

exit A 2 3

exit cd ..

exit 42 42 42 42 42

exit 42 42

exit A 1

exit 1 A
```

---

## Variable Expansion

### Dollar Sign in Quotes
```bash
echo $"HOME"

echo $'HOME'

echo $"HOME"$USER

echo $"HOM"E$USER

echo $"'HOM'E"$USER

echo $'HOM'E$USER

echo $"HOME"

echo $'HOME'

echo $"$"

echo $"42$"

echo $'$'

/bin/echo $"HOME"$USER

/bin/echo $"HOM"E$USER

/bin/echo $"'HOM'E"$USER

/bin/echo $'HOM'E$USER

/bin/echo $"HOME"

/bin/echo $'HOME'

/bin/echo $"$"

/bin/echo $"42$"

/bin/echo $'$'
```

### Exit Status Variable
```bash
/bin/echo ""$?""
/bin/echo " "$?" "
/bin/echo $?"42"
/bin/echo ''$?''"42"
/bin/echo 'HELLO'$?:''"42"

/bin/cat 42
echo $?

/bin/echo 42
expr $? + $?

/bin/cat 42
expr $? + $?
```

### Dollar Sign Combinations
```bash
echo '$'$'$'$'$'

echo '$'$'$'$'$'$'$'

echo "$"$'$'$"$"$"$"$'$'
```

### Undefined Variables
```bash
$NOVAR

export T="s"
l$T

export T="s"
l$T -a

export T="l"
$Ts

export T="l"
$Ts -a
```

### Command in Variable
```bash
export tmp_test="/bin/echo 42"
$tmp_test
$tmp_test 42
export tmp_test="/bin/echo"
$tmp_test 42 42

export tmp_test="/bin/echo 42"
"tmp_test"

export T="echo segfault | grep segfault"
$T
```

### Variable Splitting
```bash
export X="  A  B  "
/bin/echo "1"$X'2'

export X=" A  B  "
/bin/echo "1"$X'2'

export X="A  B  "
/bin/echo "1"$X'2'

export X="  A  B "
/bin/echo "1"$X'2'

export X="  A  B"
/bin/echo "1"$X'2'

export X="  A B  "
/bin/echo "1"$X'2'

export X="  AB  "
/bin/echo "1"$X'2'

export X="  A  B  "
/bin/echo $X'2'

export X="  A  B  "
/bin/echo $X"1"

export X=""
/bin/echo "1"$X'2'

export X=" "
/bin/echo "1"$X'2'

export X="   "
/bin/echo "1"$X'2'

export X="  A  B  "
/bin/echo ?$X'2'

export X="  A  B  "
/bin/echo "1"$X?

export X="  A  B  "
/bin/echo "1"$X2?

export test="arg1	arg2"
echo 'echo $1' > tmp_test_sh
bash tmp_test_sh $test
echo 'echo $2' > tmp_test_sh
bash tmp_test_sh $test
rm -f tmp_test_sh
```

---

## Quoting & Escaping

### Backslash Escaping
```bash
echo \$USER

echo \\$USER

echo \\\$USER

echo \\\\$USER

echo \\\\\$USER

echo \\\\\\\\\$USER

echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \$PATH \\$PWD

/bin/echo \$USER

/bin/echo \\$USER

/bin/echo \\\$USER

/bin/echo \\\\$USER

/bin/echo \\\\\$USER

/bin/echo \\\\\\\\\$USER

/bin/echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \$PATH \\$PWD
```

### Quote Combinations
```bash
echo '"'"$USER"'"'

/bin/echo '"'"$USER"'"'

echo """""""'"$USER"'"""""""

/bin/echo """""""'"$USER"'"""""""

echo ""'""'""""$USER""""'""'""

/bin/echo ""'""'""""$USER""""'""'""

echo " test1 test2 " 'test3 '

'''''''''''''''' echo ok
```

---

## Pipes

### Basic Pipe Tests
```bash
cat ./test_files/infile_big | grep oi

/bin/echo 1 | grep 2

ifconfig | grep nothing

echo 42 | echo no | echo smth | grep 42

echo 42 | echo no | echo smth | grep no

/bin/echo 1 | kaka

cat tmp_lol.c | cat > tmp_lol.c
rm -rf tmp_lol.c

ls | cat asd
```

### Pipe with Redirection
```bash
echo <"./test_files/infile_big" | cat <"./test_files/infile"

echo <"./test_files/infile_big" | cat "./test_files/infile"

echo hi | cat <"./test_files/infile"

echo hi | cat "./test_files/infile"

cat <"./test_files/infile" | grep hello

cat <missing | cat <"./test_files/infile"

/bin/echo 1 >/dev/null | /usr/bin/grep 1

/bin/echo >/dev/null 1 | /usr/bin/grep 1

echo 1 | >tmp_out
cat tmp_out
rm -f tmp_out
```

### Pipes as Variables
```bash
export T="|"
echo segfault $T grep segfault

export T='|'
echo segfault $T grep segfault

export T="|"
$T$T$T$T$T$T$T

export T='|'
echo $T echo lala $T echo $T echo ?
```

### Multiple Pipes
```bash
ls|cat Makefile|<wc -l

ls|cat Makefile|> out
/bin/rm -f out

ls|cat Makefile|>> out
/bin/rm -f out
```

---

## Redirections

### Basic Redirections
```bash
/bin/echo 42 > tmp_redir_out 42
cat tmp_redir_out
rm tmp_redir_out

>">" asd
/bin/rm -f ">"

>| echo sure

>echo>
/bin/rm -f echo

<echo<
/bin/rm -f echo

>>echo>>
/bin/rm -f echo
```

### Redirections with Variables
```bash
export T=">>"
$T lol

export T=">"
echo segfault $T grep segfault

export T='<'
echo segfault $T grep segfault

export T="<<"
echo segfault $T grep segfault

export T='<<'
echo segfault $T grep segfault
```

### Multiple Redirections
```bash
ls > out >> out1 >out3 | cat out1
ls > out >> out1 >out3 | cat out1
/bin/rm -f out
/bin/rm -f out1
/bin/rm -f out3

cat < Makefile > out >> out1 | wc -l out1 > out2
cat < Makefile > out >> out1 | wc -l out1 > out2
/bin/rm -f out
/bin/rm -f out1
/bin/rm -f out2

cat Makefile | ls > out
cat out
/bin/rm -f out
```

### Permissions Test
```bash
/bin/echo '\1$42' > tmp_redir_out
ls -la | grep tmp_redir_out | awk '{print $1 $2}'
cat -e tmp_redir_out
rm tmp_redir_out
```

---

## Heredoc

### Basic Heredoc
```bash
cat << lim
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

<<lim cat
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

cat << lim
test
lim

cat << EOF
"EOF"
!! HELLO
@42 !!
 EOF\t\b\n
testing your minishell :)
limm
EOF
```

### Heredoc with Variable Expansion
```bash
cat << hello
$USER
$NOVAR
$HOME
hello

cat << $USER
why
not
$USER

cat << "$USER"
why
not
$USER

cat << "$US"E"R"
because
we
love
bash
$USER
```

### Heredoc with Quotes
```bash
cat << 'lim'
$USER
$NOVAR
$HOME
lim

cat << lim''
$USER
$NOVAR
$HOME
lim

cat << "lim"
$USER
$NOVAR
$HOME
lim
```

### Heredoc in Pipes
```bash
ls | cat << stop | grep "asd"
is this good
stop

ls | cat << stop | ls -la | cat << stop1
12
32232
23
stop
awdaw
daswd
stop1

ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la | cat << stop3
$USER
ad
as $HOME
stop
awd
wf$PWDdqwdwqd
stop1
das
das
stop2
dsq
wd
wf$PWDdqwdwqd
stop3

ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > out | cat << 'stop3'
$USER
ad
stop
dsa
stop1
sad
stop2
as $HOME
stop3
/bin/rm -f out

ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3
fe
wf
fwe
f
stop
dw
stop1
dwasd
stop2
cat Makefile | ls > out
cat out
/bin/rm -f out

ls | cat << stop | ls -la > out0| cat << stop1 | ls | cat << stop2 | ls -la >> out | cat << stop3
fe
wf
fwe
f
stop
dw
stop1
dw
stop2
e
wf
stop3
/bin/rm -f out
/bin/rm -f out0

ls|cat Makefile|cat<<asd>out
$USER
asd
/bin/rm -f out

ls|cat Makefile|cat<<'asd'>out
$USER
asd
/bin/rm -f out

ls|cat Makefile|cat<<"asd">out
$USER
asd
/bin/rm -f out
```

### Heredoc with Special Delimiter
```bash
export T="<<"
$T.
```

---

## PATH Handling

### PATH Modifications
```bash
export PATH=""
echo $PATH
cd -

export PATH=
echo $PATH
echo 1

export PATH=1
echo $PATH
echo 1

export PATH=""
ls
```

### PATH Tests
```bash
mkdir tmp_path_test1 tmp_path_test2
printf '#include <unistd.h>\nint main(){write(1, \"1\\n\", 2);}' > tmp_path_test1/test1.c
gcc tmp_path_test1/test1.c -o tmp_path_test1/a.out
printf '#include <unistd.h>\nint main(){write(1, \"2\\n\", 2);}' > tmp_path_test2/test2.c
gcc tmp_path_test2/test2.c -o tmp_path_test2/a.out
export PATH=tmp_path_test1:tmp_path_test2
a.out
export PATH=tmp_path_test2:tmp_path_test1
a.out
/bin/rm -rf tmp_path_test1 tmp_path_test2
```

### Execution without PATH
```bash
touch tmp_x_file1
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
export PATH=$HOME
echo $PATH
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
unset PATH
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
echo 42
/bin/rm -f tmp_x_file1
```

---

## Command Execution

### Empty Commands
```bash
""

cat cmds.sh
```

### Special Path Cases
```bash
"."

./ls

"./"ls

"./""ls"

"./"''"ls"

/ls

/bin/

~

.

..

/
```

### File Creation Edge Cases
```bash
touch ""

touch "
"
/bin/rm -f "
"
```

### Invalid Commands
```bash
hello world
||||||||
```

### Command Execution Context
```bash
echo "ls" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

echo "unset PATH" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?
```

---

## Edge Cases & Special Cases

### Empty and Whitespace
```bash
""

echo "  "Hello "World "

echo '  ' Hello World

echo '  'Hello 'World '

echo " "" " ' ' " " ' ' " "
```

### Special Characters in Files
```bash
cat 42 42

/bin/cat 42
```
