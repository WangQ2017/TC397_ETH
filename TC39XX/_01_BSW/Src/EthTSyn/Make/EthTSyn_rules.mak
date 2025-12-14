############################################################################### 
# File Name  : EthTSyn_rules.mak 
# Description: Rules makefile 
#-----------------------------------------------------------------------------
# COPYRIGHT
#-----------------------------------------------------------------------------
# Copyright (c) 2019 by Vector Informatik GmbH.  All rights reserved.
#-----------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Version   Date        Author  Description
#------------------------------------------------------------------------------
# 1.00.00   2014-08-28  visdmi  Created
# 2.00.00   2016-07-26  vissem  EthTSyn Switch Management submodule source file
#                               added
# 3.00.00   2017-06-08  vissem  Introduced Wildecard to match all EthTSyn
#                               source files without further adaptions
# 4.00.00   2017-11-20  vissem  Updated to template version 1.01
# 5.00.00   2019-02-20  vissem  Added support of component-based SIP structure
#------------------------------------------------------------------------------
# TemplateVersion = 1.01
###############################################################################

# Component Files
CC_FILES_TO_BUILD       += EthTSyn$(BSW_SRC_DIR)\EthTSyn*.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\EthTSyn_Lcfg.c

# Library Settings
LIBRARIES_TO_BUILD      += EthTSyn
EthTSyn_FILES            = EthTSyn$(BSW_SRC_DIR)\EthTSyn*.c