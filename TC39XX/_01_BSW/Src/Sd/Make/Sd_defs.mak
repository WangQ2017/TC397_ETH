############################################################################### 
# File Name  : Sd_defs.mak 
# Description: Public makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2019 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Refer to the Sd_rules.mak file.
############################################################################### 
SD_CORE_PATH       = Sd\
SD_OUTPUT_PATH     = $(GENDATA_DIR)
#CAN_TOOL_PATH       = $(PROJECT_ROOT)\core\com\can\gentool 
# it is also possible to generate own configurations with some checks like the following example 
#  ifneq ( $(CAN_CONFIG_PATH),) 
#      CAN_PROJECT_PATH    = $(CAN_CONFIG_PATH) 
#  else 
#     CAN_PROJECT_PATH    = $(PROJECT_ROOT)\source\network\can 
#  endif  
############################################################### 
# REGISTRY 
#  
# $(SSC_PLUGINS) is a list of the components. Here can is added (not necessary for Vector, whole component-list also exists in Global.makefile.target.make...) 
# e.g.: SSC_PLUGINS        += can 
SSC_PLUGINS        +=  
#e.g.: can_DEPENDENT_PLUGINS =  
SD_DEPENDENT_PLUGINS =  
#----------------------------------------------------------------------------------------- 
# MakeSupport usually includes all header-files which were in the same 
# directory as the source-files automatically, but to ensure that the 
# Asr-Makefiles will also work with other Basic-Make-Packages, 
# it is necessary to define all include directories for this Module 
# e.g.: CC_INCLUDE_PATH     += $(CAN_CORE_PATH) 
#------------------------------------------------------------------------------------------ 
CC_INCLUDE_PATH     += 
CPP_INCLUDE_PATH    += 
ASM_INCLUDE_PATH    += 
#PREPROCESSOR_DEFINES+= drivermode 
#drivermode_KEY       = CAN_MODE 
#drivermode_VALUE    = $(CAN_DRIVER_MODE) 
############################################################### 
# PROVIDE 
# 
# A Public Makefile does not provide resources for other basic 
# software bundles or the base_make package. 
############################################################### 
