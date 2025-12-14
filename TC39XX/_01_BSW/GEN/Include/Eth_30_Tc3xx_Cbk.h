/**********************************************************************************************************************
*  FILE REQUIRES USER MODIFICATIONS
*  Template Scope: whole file 
*  -------------------------------------------------------------------------------------------------------------------
* This file includes template code that must be adapted during BSW integration.
* The template code is incomplete and only intended for providing a signature and an empty implementation.
* It is neither intended nor qualified for use in series production without applying suitable quality measures. 
* The template code must be completed as described in the instructions given within this file and in the 
* Technical Reference. 
* The completed implementation must be tested with diligent care and must comply with all quality requirements which 
* are necessary according to the state of the art before its use.
*********************************************************************************************************************/
#if !defined(ETH_30_TC3XX_CBK_H)
# define ETH_30_TC3XX_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "ComStack_Types.h"
# include "Platform_Types.h"
# include "Compiler.h"
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
# ifndef ETH_30_TC3XX_CBK_LOCAL_INLINE
#  define ETH_30_TC3XX_CBK_LOCAL_INLINE                                LOCAL_INLINE
# endif
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  Appl_Eth_30_Tc3xx_MemoryBarrier
 **********************************************************************************************************************/
/*! \brief        This callout function must be provided by the application and it provides memory barrier
 *  \details      The function shall provide a platform and compiler specific memory barrier so that following memory
 *                and register accesses are synchronized.
 *  \context      ANY
 *  \synchronous  TRUE
 *  \reentrant    TRUE
 *  \pre          -
 */
ETH_30_TC3XX_CBK_LOCAL_INLINE FUNC (void, ETH_30_TC3XX_CODE) Appl_Eth_30_Tc3xx_MemoryBarrier(void);

/***********************************************************************************************************************
 *  Appl_Eth_30_Tc3xx_MemoryBarrier
 **********************************************************************************************************************/
/*! \brief        This callout function must be provided by the application and it provides a memory barrier
 *  \details      The function shall provide a platform and compiler specific memory barrier so that following memory
 *                and peripheral register accesses are synchronized.
 *  \context      ANY
 *  \synchronous  TRUE
 *  \reentrant    TRUE
 *  \pre          -
 */
ETH_30_TC3XX_CBK_LOCAL_INLINE FUNC (void, ETH_30_TC3XX_CODE) Appl_Eth_30_Tc3xx_MemoryBarrier(void)
{
  __dsync();
  __isync();
}
#endif /* ETH_30_TC3XX_CBK_H */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Cbk.h
 *********************************************************************************************************************/
