################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/MemMang/heap_2.obj: ../FreeRTOS/portable/MemMang/heap_2.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/pgnanasekaran/newworkspace_v8/hw5_q3" --include_path="C:/Users/pgnanasekaran/Desktop/FreeRTOSv10.0.1/FreeRTOS/Source/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/MemMang/heap_2.d_raw" --obj_directory="FreeRTOS/portable/MemMang" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


