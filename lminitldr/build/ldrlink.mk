include krnlbuidcmd.mh
include ldrobjs.mh
.PHONY : all everything build_kernel
all: build_kernel 
#LMOSLDR
build_kernel:everything
everything : $(LMOSLDRIMH) $(LMOSLDRKRL) $(LMOSLDRSVE)

$(LMOSLDRIMH): $(LMOSLDRIMH_LINK)
	$(LD) $(LDRIMHLDFLAGS) -o $@ $(LMOSLDRIMH_LINK)
$(LMOSLDRKRL): $(LMOSLDRKRL_LINK)
	$(LD) $(LDRKRLLDFLAGS) -o $@ $(LMOSLDRKRL_LINK)
$(LMOSLDRSVE): $(LMOSLDRSVE_LINK)
	$(LD) $(LDRSVELDFLAGS) -o $@ $(LMOSLDRSVE_LINK)

LMOSLDR:
	$(LDRIMG) $(LDRIMGFLAGS) -lhf $(LMOSLDRIMH) -o lmoskrnl.eki -f $(LMOSLDRKRL) $(LMOSLDRSVE) lmoskrnl lmosinitshell
