################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./senior_cla_cpu1.obj" \
"./senior_main_cpu1.obj" \
"./Senior Source/Senior_ADC.obj" \
"./Senior Source/Senior_CLA.obj" \
"./Senior Source/Senior_DMA.obj" \
"./Senior Source/Senior_FFT.obj" \
"./Senior Source/Senior_SCI.obj" \
"./Senior Source/Senior_SPI.obj" \
"./Senior Source/Senior_ePWM.obj" \
"./Source/F2837xD_Adc.obj" \
"./Source/F2837xD_CodeStartBranch.obj" \
"./Source/F2837xD_DefaultISR.obj" \
"./Source/F2837xD_Dma.obj" \
"./Source/F2837xD_EPwm.obj" \
"./Source/F2837xD_GlobalVariableDefs.obj" \
"./Source/F2837xD_Gpio.obj" \
"./Source/F2837xD_Ipc.obj" \
"./Source/F2837xD_Ipc_Driver.obj" \
"./Source/F2837xD_Ipc_Driver_Util.obj" \
"./Source/F2837xD_PieCtrl.obj" \
"./Source/F2837xD_PieVect.obj" \
"./Source/F2837xD_Spi.obj" \
"./Source/F2837xD_SysCtrl.obj" \
"./Source/F2837xD_sci_io.obj" \
"./Source/F2837xD_usDelay.obj" \
"../F2837xD_Headers_nonBIOS_cpu1.cmd" \
$(GEN_CMDS__FLAG) \
-l"C:/ti/c2000/C2000Ware_1_00_05_00/libraries/dsp/FPU/c28/lib/c28x_fpu_dsp_library.lib" \
-l"C:/Users/meserwinowski/OneDrive - University of Florida/UF/Senior Design EEL4924C/senior_pitch_analyzer/senior_main_cpu01/Linker/F2837xD_FLASH_lnk_cpu1.cmd" \
-lrts2800_fpu32.lib \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Senior\ Source/subdir_vars.mk
-include Source/subdir_vars.mk
-include subdir_rules.mk
-include Senior\ Source/subdir_rules.mk
-include Source/subdir_rules.mk
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
senior_main_cpu01.out \

EXE_OUTPUTS__QUOTED += \
"senior_main_cpu01.out" \

BIN_OUTPUTS += \
senior_main_cpu01.hex \

BIN_OUTPUTS__QUOTED += \
"senior_main_cpu01.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "senior_main_cpu01.out"

# Tool invocations
senior_main_cpu01.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O2 --fp_mode=relaxed --advice:performance=all --define=CPU1 --define=_STANDALONE --define=_FLASH --define=CLA_C --define=RFFT_ALIGNMENT=2048 --define=_LAUNCHXL_F28379D -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics -z -m"senior_main_cpu01.map" --stack_size=0x200 --warn_sections -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" -i"C:/Users/meserwinowski/OneDrive - University of Florida/UF/Senior Design EEL4924C/senior_pitch_analyzer" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="senior_main_cpu01_linkInfo.xml" --entry_point=_c_int00 --rom_model -o "senior_main_cpu01.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

senior_main_cpu01.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/hex2000"  -o "senior_main_cpu01.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "senior_cla_cpu1.obj" "senior_main_cpu1.obj" "Senior Source\Senior_ADC.obj" "Senior Source\Senior_CLA.obj" "Senior Source\Senior_DMA.obj" "Senior Source\Senior_FFT.obj" "Senior Source\Senior_SCI.obj" "Senior Source\Senior_SPI.obj" "Senior Source\Senior_ePWM.obj" "Source\F2837xD_Adc.obj" "Source\F2837xD_CodeStartBranch.obj" "Source\F2837xD_DefaultISR.obj" "Source\F2837xD_Dma.obj" "Source\F2837xD_EPwm.obj" "Source\F2837xD_GlobalVariableDefs.obj" "Source\F2837xD_Gpio.obj" "Source\F2837xD_Ipc.obj" "Source\F2837xD_Ipc_Driver.obj" "Source\F2837xD_Ipc_Driver_Util.obj" "Source\F2837xD_PieCtrl.obj" "Source\F2837xD_PieVect.obj" "Source\F2837xD_Spi.obj" "Source\F2837xD_SysCtrl.obj" "Source\F2837xD_sci_io.obj" "Source\F2837xD_usDelay.obj" 
	-$(RM) "senior_main_cpu1.d" "Senior Source\Senior_ADC.d" "Senior Source\Senior_CLA.d" "Senior Source\Senior_DMA.d" "Senior Source\Senior_FFT.d" "Senior Source\Senior_SCI.d" "Senior Source\Senior_SPI.d" "Senior Source\Senior_ePWM.d" "Source\F2837xD_Adc.d" "Source\F2837xD_DefaultISR.d" "Source\F2837xD_Dma.d" "Source\F2837xD_EPwm.d" "Source\F2837xD_GlobalVariableDefs.d" "Source\F2837xD_Gpio.d" "Source\F2837xD_Ipc.d" "Source\F2837xD_Ipc_Driver.d" "Source\F2837xD_Ipc_Driver_Util.d" "Source\F2837xD_PieCtrl.d" "Source\F2837xD_PieVect.d" "Source\F2837xD_Spi.d" "Source\F2837xD_SysCtrl.d" "Source\F2837xD_sci_io.d" 
	-$(RM) "senior_cla_cpu1.d" 
	-$(RM) "Source\F2837xD_CodeStartBranch.d" "Source\F2837xD_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

