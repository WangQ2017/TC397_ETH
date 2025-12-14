############################################################################### 
# File Name  : UdpNm_defs.mak 
# Description: Public makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2019 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Refer to the UdpNm_rules.mak file.
############################################################################### 

#-----------------------------------------------------------------------------------------
# MakeSupport usually includes all header-files which were in the same
# directory as the source-files automatically, but to ensure that the
# Asr-Makefiles will also work with other Basic-Make-Packages,
# it is necessary to define all include directories for this Module
# e.g.: CC_INCLUDE_PATH     += $(CAN_CORE_PATH)
#------------------------------------------------------------------------------------------
CC_INCLUDE_PATH     += UdpNm$(BSW_SRC_DIR) $(GENDATA_DIR)
