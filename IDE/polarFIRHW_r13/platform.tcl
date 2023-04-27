# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\ComplexFIRFilter\IDE\polarFIRHW_r13\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\ComplexFIRFilter\IDE\polarFIRHW_r13\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {polarFIRHW_r13}\
-hw {D:\ComplexFIRFilter\hw\polarFIRhw_r13.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {D:/ComplexFIRFilter/IDE}

platform write
platform generate -domains 
platform active {polarFIRHW_r13}
platform generate
