############################################################################### 
# File Name  : EthIf_rules.mak 
# Description: Rules makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2019 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Version   Date        Author  Description
#------------------------------------------------------------------------------
# 1.00.00   2008-11-19  visalr  Created
# 1.00.03   2009-10-08  visalr  bugfix library support
# 2.00.00   2013-08-05  vishaw  MSR4-R8 support
# 2.01.00   2014-03-04  vishaw  PTP support
# 2.02.00   2014-07-08  vishaw  ESCAN00077151: AR4-500:
#                               AUTOSAR CONC_600_SwitchConfiguration
# 2.03.00   2015-02-16  vismha  Removed PB config related parts
# 2.04.00   2015-06-22  vismha  Extended Traffic Handling source files added
# 2.05.00   2015-11-25  vismha  Introduced files containing switch hardware
#                               abstraction implementation
# 3.00.00   2016-06-15  vismha  Introduced files for Zero Copy extensions
#                               Renamed EthIf_Ptp.h/.c files to EthIf_Time.h/.c
# 4.00.00   2017-09-29  vismha  Introduced wildcard for defining files to
#                               compile
# 5.00.00   2017-11-16  vismha  Updated to latest template
# 5.00.01   2019-02-06  vircbl  Added support of component-based SIP structure
#                       vismha  Introduced wildcard for GenData files
# 6.00.00   2019-05-21  vismha  Introduced generic sub-module handling
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################

# Component Files

# Handle EthIf and it's sub-modules in a generic way to be able to add/remove
# sub-modules without the need of modification of the EthIf_rules.mak
# 1) Get relative path to EthIf implementation dir
# 2) Normalize the EthIf implementation dir path by exchanging \ with /
# 3) Get a alphabetically sorted and deduplicated list of all sub-dirs and
#    main-dir
# 4) Remove last / from sub-dirs so they can be added to MakeSupport
#    CC_INCLUDE_PATH and be used for EthIf*.c file query
# 5) Query for all EthIf*.c files that must be build
# 6) Remove relative dir path from every EthIf*.c file so we have a path that
#    the MakeSupport expects to be passed to CC_FILES_TO_BUILD
EthIf_MainDirRaw  = $(ROOT)/$(GLOBAL_COMP_DIR)/EthIf$(BSW_SRC_DIR)
EthIf_MainDir     = $(subst \,/,$(EthIf_MainDirRaw))
EthIf_DirsRaw     = $(sort $(dir $(wildcard $(EthIf_MainDir)/*/)))
EthIf_Dirs        = $(patsubst %/,%,$(subst \,/,$(EthIf_DirsRaw)))
EthIf_CFilesRaw   = $(foreach dir,$(EthIf_Dirs),$(wildcard $(dir)/EthIf*.c))
EthIf_CFiles      = $(patsubst $(EthIf_MainDir)/%,EthIf$(BSW_SRC_DIR)/%,$(EthIf_CFilesRaw))

CC_FILES_TO_BUILD       += $(EthIf_CFiles)
CC_INCLUDE_PATH         += $(EthIf_Dirs)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\EthIf_*.c

# Library Settings
LIBRARIES_TO_BUILD      += EthIf
EthIf_FILES             += $(EthIf_CFiles)
