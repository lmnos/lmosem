# !/bin/bash
echo "Start......"
echo "LMOS all code line:"
find  . -name "*.inc" -o -name "*.asm" -o -name "*.S" -o -name "*.h" -o -name "*.c" | xargs cat|grep -v ^$| wc -l | sort -n
echo "LMOS ASM code line:"
find  . -name "*.S" -o -name "*.asm" | xargs cat|grep -v ^$| wc -l | sort -n
echo "LMOS C code line:"
find  . -name "*.c" | xargs cat|grep -v ^$| wc -l | sort -n
echo "LMOS H code line:"
find  . -name "*.h" -o -name "*.inc" | xargs cat|grep -v ^$| wc -l | sort -n
echo "End!"