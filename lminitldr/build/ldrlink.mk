include krnlbuidcmd.mh
include ldrobjs.mh
.PHONY : all everything build_kernel
all: build_kernel 
#LMOSLDR
build_kernel:everything build_bin
everything : $(LMOSLDRIMH_ELF) $(LMOSLDRKRL_ELF) $(LMOSLDRSVE_ELF)
build_bin:$(LMOSLDRIMH) $(LMOSLDRKRL) $(LMOSLDRSVE)

$(LMOSLDRIMH_ELF): $(LMOSLDRIMH_LINK)
	$(LD) $(LDRIMHLDFLAGS) -o $@ $(LMOSLDRIMH_LINK)
$(LMOSLDRKRL_ELF): $(LMOSLDRKRL_LINK)
	$(LD) $(LDRKRLLDFLAGS) -o $@ $(LMOSLDRKRL_LINK)
$(LMOSLDRSVE_ELF): $(LMOSLDRSVE_LINK)
	$(LD) $(LDRSVELDFLAGS) -o $@ $(LMOSLDRSVE_LINK)
$(LMOSLDRIMH):$(LMOSLDRIMH_ELF)
	$(OBJCOPY) $(OJCYFLAGS) $< $@
	@echo 'OBJCOPY -[M] 正在构建...' $@  
$(LMOSLDRKRL):$(LMOSLDRKRL_ELF)
	$(OBJCOPY) $(OJCYFLAGS) $< $@
	@echo 'OBJCOPY -[M] 正在构建...' $@ 
$(LMOSLDRSVE):$(LMOSLDRSVE_ELF)
	$(OBJCOPY) $(OJCYFLAGS) $< $@
	@echo 'OBJCOPY -[M] 正在构建...' $@ 