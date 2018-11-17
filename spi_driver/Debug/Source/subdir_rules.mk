################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Source/F2837xD_CodeStartBranch.obj: ../Source/F2837xD_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver" --include_path="C:/ti/F2837xD/Device_support/F2837xD_headers/include" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --define=CPU1 --define=_LAUNCHXL_F28379D -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xD_CodeStartBranch.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xD_DefaultISR.obj: ../Source/F2837xD_DefaultISR.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver" --include_path="C:/ti/F2837xD/Device_support/F2837xD_headers/include" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --define=CPU1 --define=_LAUNCHXL_F28379D -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xD_DefaultISR.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xD_GlobalVariableDefs.obj: ../Source/F2837xD_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver" --include_path="C:/ti/F2837xD/Device_support/F2837xD_headers/include" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --define=CPU1 --define=_LAUNCHXL_F28379D -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xD_GlobalVariableDefs.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xD_Gpio.obj: ../Source/F2837xD_Gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver" --include_path="C:/ti/F2837xD/Device_support/F2837xD_headers/include" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --define=CPU1 --define=_LAUNCHXL_F28379D -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xD_Gpio.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xD_PieCtrl.obj: ../Source/F2837xD_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver" --include_path="C:/ti/F2837xD/Device_support/F2837xD_headers/include" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --define=CPU1 --define=_LAUNCHXL_F28379D -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xD_PieCtrl.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xD_PieVect.obj: ../Source/F2837xD_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver" --include_path="C:/ti/F2837xD/Device_support/F2837xD_headers/include" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --define=CPU1 --define=_LAUNCHXL_F28379D -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xD_PieVect.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xD_SysCtrl.obj: ../Source/F2837xD_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver" --include_path="C:/ti/F2837xD/Device_support/F2837xD_headers/include" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --define=CPU1 --define=_LAUNCHXL_F28379D -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xD_SysCtrl.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xD_usDelay.obj: ../Source/F2837xD_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver" --include_path="C:/ti/F2837xD/Device_support/F2837xD_headers/include" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --define=CPU1 --define=_LAUNCHXL_F28379D -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xD_usDelay.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


