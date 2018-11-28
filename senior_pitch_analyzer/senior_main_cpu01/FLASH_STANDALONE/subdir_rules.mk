################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
senior_cla_cpu1.obj: ../senior_cla_cpu1.cla $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O2 --fp_mode=relaxed --include_path="C:/Users/meserwinowski/OneDrive - University of Florida/UF/Senior Design EEL4924C/senior_pitch_analyzer/senior_main_cpu01" --include_path="C:/ti/controlSUITE/libs/dsp/FPU/v1_50_00_00/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/meserwinowski/OneDrive - University of Florida/UF/Senior Design EEL4924C/senior_pitch_analyzer/Source Code/Senior Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 --define=_STANDALONE --define=_FLASH --define=CLA_C --define=RFFT_ALIGNMENT=2048 --define=_LAUNCHXL_F28379D -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --preproc_with_compile --preproc_dependency="senior_cla_cpu1.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

senior_main_cpu1.obj: ../senior_main_cpu1.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O2 --fp_mode=relaxed --include_path="C:/Users/meserwinowski/OneDrive - University of Florida/UF/Senior Design EEL4924C/senior_pitch_analyzer/senior_main_cpu01" --include_path="C:/ti/controlSUITE/libs/dsp/FPU/v1_50_00_00/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/meserwinowski/OneDrive - University of Florida/UF/Senior Design EEL4924C/senior_pitch_analyzer/Source Code/Senior Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 --define=_STANDALONE --define=_FLASH --define=CLA_C --define=RFFT_ALIGNMENT=2048 --define=_LAUNCHXL_F28379D -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --preproc_with_compile --preproc_dependency="senior_main_cpu1.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


