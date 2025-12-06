############################################################################### 
# File Name  : Os_rules.mak 
# Description: Rules makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2020 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Version   Date        Author  Description
#------------------------------------------------------------------------------
# 1.01.00   2016-03-24  Dfe     Initial Version
# 1.03.00   2019-02-06  vircbl  Added support of component-based SIP structure
# 1.03.00   2019-02-11  Rework  to match the template
# 1.04.00   2019-06-27  visto   Added Diab Compiler file
# 1.05.00   2019-07-25  visdri  Added GHS Compiler file
# 1.06.00   2020-05-13  virrlu  Added Tasking Compiler file
# 2.00.00   2020-09-28  vismun  Support to new TLM
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################

# Include of OS Core makefile

-include $(ROOT)\$(GLOBAL_COMP_DIR)\Os\$(if $(BSW_MAKE_DIR),$(BSW_MAKE_DIR),mak)\Os_Core.mak

# In case of new TLM

NEW_TLM_PATH = ..\internal\external
-include $(ROOT)\$(NEW_TLM_PATH)\$(GLOBAL_COMP_DIR)\Os\$(if $(BSW_MAKE_DIR),$(BSW_MAKE_DIR),mak)\Os_Core.mak


# Component Files

CC_FILES_TO_BUILD       +=  Os$(BSW_SRC_DIR)\Os_Hal_Context.c      \
                            Os$(BSW_SRC_DIR)\Os_Hal_Core.c         \
                            Os$(BSW_SRC_DIR)\Os_Hal_Entry.c        \
                            Os$(BSW_SRC_DIR)\Os_Hal_Trap.c         \
                            Os$(BSW_SRC_DIR)\Os_Hal_Compiler_HighTec.c \
                            Os$(BSW_SRC_DIR)\Os_Hal_Compiler_Diab.c \
                            Os$(BSW_SRC_DIR)\Os_Hal_Compiler_Greenhills.c \
                            Os$(BSW_SRC_DIR)\Os_Hal_Compiler_Tasking.c

ASM_FILES_TO_BUILD      +=

GENERATED_SOURCE_FILES  +=  $(GENDATA_DIR)\Os_Hal_Context_Lcfg.c          \
                            $(GENDATA_DIR)\Os_Hal_Core_Lcfg.c             \
                            $(GENDATA_DIR)\Os_Hal_Entry_Lcfg.c            \
                            $(GENDATA_DIR)\Os_Hal_Interrupt_Lcfg.c        \
                            $(GENDATA_DIR)\Os_Hal_Kernel_Lcfg.c           \
                            $(GENDATA_DIR)\Os_Hal_MemoryProtection_Lcfg.c \
                            $(GENDATA_DIR)\Os_Hal_Timer_Lcfg.c


# Library Settings
# Library not supported
