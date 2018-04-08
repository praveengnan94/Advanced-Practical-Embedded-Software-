################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.o" \
"./tm4c1294ncpdt_startup_ccs.o" \
"./tm4c1294ncpdt_startup_ccs_gcc.o" \
"./FreeRTOS/event_groups.o" \
"./FreeRTOS/heap_2.o" \
"./FreeRTOS/list.o" \
"./FreeRTOS/queue.o" \
"./FreeRTOS/tasks.o" \
"./FreeRTOS/timers.o" \
"./FreeRTOS/portable/CCS/ARM_CM4F/port.o" \
"./FreeRTOS/portable/CCS/ARM_CM4F/portasm.o" \
"./utilities/uartstdio.o" \
-Wl,-T"../tm4c1294ncpdt.cmd" \
-Wl,-T"../tm4c1294ncpdt.lds" \
$(GEN_CMDS__FLAG) \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include FreeRTOS/subdir_vars.mk
-include FreeRTOS/portable/CCS/ARM_CM4F/subdir_vars.mk
-include utilities/subdir_vars.mk
-include subdir_rules.mk
-include FreeRTOS/subdir_rules.mk
-include FreeRTOS/portable/CCS/ARM_CM4F/subdir_rules.mk
-include utilities/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
hw5_q4.out \

EXE_OUTPUTS__QUOTED += \
"hw5_q4.out" \

BIN_OUTPUTS += \
hw5_q4.hex \

BIN_OUTPUTS__QUOTED += \
"hw5_q4.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LDS_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "hw5_q4.out"

# Tool invocations
hw5_q4.out: $(OBJS) $(CMD_SRCS) $(LDS_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: GNU Linker'
	"C:/ti/ccsv8/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/bin/arm-none-eabi-gcc.exe" -DPART_TM4C1294NCPDT -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -specs="nosys.specs" -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wl,-Map,"hw5_q4.map" -o"hw5_q4.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

hw5_q4.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: GNU Objcopy Utility'
	"C:/ti/ccsv8/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/bin/arm-none-eabi-objcopy.exe"  $(EXE_OUTPUTS__QUOTED) "hw5_q4.hex"
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.o" "tm4c1294ncpdt_startup_ccs.o" "tm4c1294ncpdt_startup_ccs_gcc.o" "FreeRTOS\event_groups.o" "FreeRTOS\heap_2.o" "FreeRTOS\list.o" "FreeRTOS\queue.o" "FreeRTOS\tasks.o" "FreeRTOS\timers.o" "FreeRTOS\portable\CCS\ARM_CM4F\port.o" "FreeRTOS\portable\CCS\ARM_CM4F\portasm.o" "utilities\uartstdio.o" 
	-$(RM) "main.d" "tm4c1294ncpdt_startup_ccs.d" "tm4c1294ncpdt_startup_ccs_gcc.d" "FreeRTOS\event_groups.d" "FreeRTOS\heap_2.d" "FreeRTOS\list.d" "FreeRTOS\queue.d" "FreeRTOS\tasks.d" "FreeRTOS\timers.d" "FreeRTOS\portable\CCS\ARM_CM4F\port.d" "utilities\uartstdio.d" 
	-$(RM) "FreeRTOS\portable\CCS\ARM_CM4F\portasm.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

