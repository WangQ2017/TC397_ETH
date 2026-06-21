############################################################################### 
# File Name  : DoIP_rules.mak 
# Description: Rules makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2021 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Version   Date        Author      Description
#------------------------------------------------------------------------------
# 1.00.00   2013-10-18  vismda      created
# 1.01.00   2015-11-24  vismda      version history in <Msn>_rules.mak only
# 2.00.00   2019-02-06  vircbl      Added support of component-based SIP
#                                   structure
# 2.00.01   2019-04-25  visjsb      Update makefile to new template structure
# 2.00.02   2021-01-05  jelsaesser  ESCAN00107824: Compilation with make
#                                   support fails
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################

# Component Files
CC_FILES_TO_BUILD       += DoIP$(BSW_SRC_DIR)\DoIP.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\DoIP_Lcfg.c

# Library Settings
LIBRARIES_TO_BUILD      += DoIP
DoIP_FILES              += DoIP$(BSW_SRC_DIR)\DoIP.c
