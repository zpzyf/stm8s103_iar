############
# Settings #
############

# Set up build environment (using GNU Make)
#   set PATH=%PATH%;D:\Program Files\IAR Systems\Embedded Workbench 6.0\stm8\bin
#   set MAKE_MODE=DOS

# Build all test applications:
#   make -f iar.mak
# Location of build tools and atomthreads sources
EWSTM8_DIR=D:\Program Files\IAR Systems\Embedded Workbench 7.0\stm8

CC	= iccstm8
ASM = iasmstm8
LINK = ilinkstm8
ELF = ielftool
RM = del /q
MCU = STM8S103
TYPE = $(MCU)k3
TARGET = project

A_SRC := $(sort $(wildcard *.s))
C_SRC := $(sort $(wildcard *.c))
A_OBJ := $(patsubst %.s,%.o,$(A_SRC))
C_OBJ := $(patsubst %.c,%.o,$(C_SRC))



# Compiler/Assembler flags
CFLAGS = -e -Ol --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa  \
	--no_cross_call --debug --code_model small --data_model medium \
	--dlib_config "$(EWSTM8_DIR)\LIB\dlstm8smn.h" -D $(MCU) --vregs 16

LINKFLAGS = --redirect _Printf=_PrintfSmall  --redirect _Scanf=_ScanfSmall \
	--config  "$(EWSTM8_DIR)\config\lnk$(TYPE).icf" \
	--config_def _CSTACK_SIZE=0x100 --config_def _HEAP_SIZE=0x100 --entry __iar_program_start --debug_lib

all: $(TARGET).s19 $(TARGET).bin $(TARGET).hex

$(TARGET).s19 : $(TARGET).elf
	$(ELF) $< $@ --srec

$(TARGET).bin : $(TARGET).elf
	$(ELF) $< $@ --bin

$(TARGET).hex : $(TARGET).elf
	$(ELF) $< $@ --ihex

$(TARGET).elf : $(C_OBJ)
	$(LINK) $(LINKFLAGS)  -o $@ $(C_OBJ)

$(C_OBJ): %.o : %.c
	$(CC) $< $(CFLAGS) -I . --dependencies=m "$(basename $<).d" -o $@

clean:
	$(RM) *.o > nul
	$(RM) *.d > nul
	$(RM) $(TARGET).elf > nul
	$(RM) $(TARGET).s19 > nul
	$(RM) $(TARGET).hex > nul
	$(RM) $(TARGET).bin > nul


-include $(wildcard *.d)

