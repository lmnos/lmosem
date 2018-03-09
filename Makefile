###################################################################
#		主控自动化编译配置文件 Makefile			  #
#				彭东  ＠ 2012.08.13.23.50	  #
###################################################################

MAKEFLAGS = -sR

MKDIR = mkdir
RMDIR = rmdir
CP = cp
CD = cd
DD = dd
RM = rm
LKIMG = ./lmoskrlimg -m k
VM = qemu-system-x86_64
DBUGVM = bochs -q
IMGTOVDI = qemu-img convert -f raw -O vdi
IMGTOVMDK = qemu-img convert -f raw -O vmdk
MAKE = make
X86BARD = -f ./Makefile.x86

VVMRLMOSFLGS = -C $(BUILD_PATH) -f vbox.mkf

VBOXVMFLGS = -C $(VM_PATH) -f vbox.mkf
VMFLAGES = -smp 4 -hda $(VMDKFNAME) -m 256 -enable-kvm

IMGSECTNR = 204800
PHYDSK = /dev/sdb
VDIFNAME = lmos.vdi
VMDKFNAME = lmosdisk.vmd
KRNLEXCIMG = lmosemkrnl.bin

LOGOFILE = LMOSEMLOGOX.bmp 22.bmp #LMOSBKDG4.bmp DIPDRV.bmp
FONTFILE = lmos.fnt
BUILD_PATH = ./build
EXKNL_PATH = ./exckrnl
DSTPATH = ../exckrnl
RELEDSTPATH = ../release
LMINITLDR_PATH =./lminitldr/
LMILDR_BUILD_PATH =./lminitldr/build/
CPLILDR_PATH =./release/
INSTALL_PATH =/boot/
INSTALLSRCFILE_PATH =./release/lmosemkrnl.eki
SRCFILE = $(BOOTEXCIMG) $(KRNLEXCIMG) $(LDEREXCIMG) $(SHELEXCIMG)
RSRCFILE = $(BOOTEXCIMG) $(KRNLEXCIMG) $(LDEREXCIMG) $(SHELEXCIMG) #$(VDIFNAME) $(VMDKFNAME)

LMOSLDRIMH = lmldrimh.bin
LMOSLDRKRL = lmldrkrl.bin
LMOSLDRSVE = lmldrsve.bin

CPLILDRSRC= $(LMILDR_BUILD_PATH)$(LMOSLDRSVE) $(LMILDR_BUILD_PATH)$(LMOSLDRKRL) $(LMILDR_BUILD_PATH)$(LMOSLDRIMH)

LKIMG_INFILE = $(LMOSLDRSVE) $(LMOSLDRKRL) $(KRNLEXCIMG) $(SHELEXCIMG) $(FONTFILE) $(LOGOFILE) $(GIFFILE) $(GIFFILE2)
.PHONY : install x32 build print clean all krnlexc cpkrnl wrimg phymod exc vdi vdiexc cprelease release createimg

build: clean print all

all:
	$(MAKE) $(X86BARD)
	@echo '恭喜我，系统编译构建完成！ ^_^'
clean:
	$(CD) $(BUILD_PATH); $(RM) -f *.o *.bin *.i *.krnl *.s *.map *.lib *.btoj *.vdi *.elf *vmdk *.lds *.mk *.mki krnlobjs.mh
	$(CD) $(EXKNL_PATH); $(RM) -f *.o *.bin *.i *.krnl *.s *.map *.lib *.btoj *.vdi *.elf *vmdk *.lds *.mk *.mki krnlobjs.mh
	$(CD) $(CPLILDR_PATH); $(RM) -f *.o *.bin *.i *.krnl *.s *.eki *.map *.lib *.btoj *.elf *.vdi *vmdk *.lds *.mk *.mki krnlobjs.mh
	@echo '清理全部已构建文件... ^_^'

print:
	@echo '*********正在开始编译构建系统*************'


krnlexc: cpkrnl wrimg exc
dbugkrnl: cpkrnl wrimg dbugexc
vdiexc:  vdi
	$(MAKE) $(VBOXVMFLGS)
vdi:cpkrnl wrimg
	$(CD) $(EXKNL_PATH) && $(IMGTOVDI) $(DSKIMG) $(VDIFNAME)
	$(CD) $(EXKNL_PATH) && $(IMGTOVMDK) $(DSKIMG) $(VMDKFNAME)
cplmildr:
	$(CP) $(CPFLAGES) $(CPLILDRSRC) $(CPLILDR_PATH)

cpkrnl:
	$(CD) $(BUILD_PATH) && $(CP) $(CPFLAGES) $(SRCFILE) $(DSTPATH)
cprelease:
	$(CD) $(EXKNL_PATH) && $(CP) $(CPFLAGES) $(RSRCFILE) $(RELEDSTPATH)

exc:
	$(CD) $(EXKNL_PATH) && $(VM) $(VMFLAGES)
dbugexc:
	$(CD) $(EXKNL_PATH) && $(DBUGVM)

KIMG:
	@echo '正在生成LMOS内核映像文件，请稍后……'
	$(CD) $(CPLILDR_PATH) && $(LKIMG) -lhf $(LMOSLDRIMH) -o lmosemkrnl.eki -f $(LKIMG_INFILE)

KVMRUN:
	$(VM) $(VMFLAGES)
#$(MAKE) $(KVMRLMOSFLGS)

VBOXRUN:
	$(MAKE) $(VVMRLMOSFLGS)

#cpkrnl cprelease
release: clean all cplmildr cpkrnl cprelease KIMG 

kvmtest: release KVMRUN

vboxtest: release VBOXRUN


createimg:
	$(DD) bs=512 if=/dev/zero of=$(DSKIMG) count=$(IMGSECTNR)

install:
	@echo '下面将开始安装LMOS内核，请确认……'
	sudo $(CP) $(CPFLAGES) $(INSTALLSRCFILE_PATH) $(INSTALL_PATH)
	@echo 'LMOS内核已经安装完成，请重启计算机……'
