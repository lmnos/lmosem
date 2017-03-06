###################################################################
#		krnlbuidrule自动化编译配置文件 Makefile		  #
#				彭东  ＠ 2013.06.15.09.00	  #
###################################################################

CCSTR		= 	'CC -[M] 正在构建... '$<
PRINTCSTR 	=	@echo $(CCSTR) 

%.krnl : $(CCBUILDPATH)%.c
[$(CC) $(CFLAGS) -o $@ $<
[$(PRINTCSTR)
%.krnl : $(CCBUILDPATH)%.S
[$(CC) $(CFLAGS) -o $@ $<
[$(PRINTCSTR)
%.o : $(CCBUILDPATH)%.asm
[$(ASM) $(ASMFLGS) -o $@ $<
[$(PRINTCSTR)
%.o : $(CCBUILDPATH)%.c
[$(CC) $(CFLAGS) -o $@ $<
[$(PRINTCSTR)
%.o : $(CCBUILDPATH)%.S
[$(CC) $(CFLAGS) -o $@ $<
[$(PRINTCSTR)	
%.lds : $(CCBUILDPATH)%.S
[$(CC) $(CPPFLGSLDS) -o $@ $<
[$(PRINTCSTR)

%.mkh : $(CCBUILDPATH)%.S
[$(CC) $(CPPFLGSLDS) -o $@ $<
[$(PRINTCSTR)

%.mk : $(CCBUILDPATH)%.S
[$(CC) $(CPPFLGSLDS) -o $@ $<
[$(PRINTCSTR)