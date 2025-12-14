/**********************************************************************************************************************
 *  EXAMPLE CODE ONLY
 *  -------------------------------------------------------------------------------------------------------------------
 *  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
 *  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
 *  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
 *  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
 *  according to the state of the art before their use.
 *********************************************************************************************************************/


architecture TC1V1.6.2
{
  endianness
  {
    little;
  }
  space linear
  {
    id = 1;
    mau = 8;
    map (dest = bus:local_bus, size = 4G);
  }
  bus local_bus
  {
    mau = 8;
    width = 32;
  }
}

derivative mpe
{
  core vtc
  {
    architecture = TC1V1.6.2;
    copytable_space = vtc:linear;
  }
  bus local_bus
  {
    mau = 8;
    width = 32;
    map (dest = bus:vtc:local_bus, dest_offset = 0, size = 4G);
  }
  section_setup :vtc:linear
  {
    copytable (align = 4, dest = linear);
    start_address (symbol = "brsStartupEntry");
  }
  memory RegionBlock_0_DSPR_Core5
  {
    mau = 8;
    type = ram;
    size = 98304; /* 96 KiB */
    map (dest=bus:local_bus, dest_offset = 0x10000000, size = 98304);
  }
  memory RegionBlock_0_DSPR_Core4
  {
    mau = 8;
    type = ram;
    size = 98304; /* 96 KiB */
    map (dest=bus:local_bus, dest_offset = 0x30000000, size = 98304);
  }
  memory RegionBlock_0_DSPR_Core3
  {
    mau = 8;
    type = ram;
    size = 98304; /* 96 KiB */
    map (dest=bus:local_bus, dest_offset = 0x40000000, size = 98304);
  }
  memory RegionBlock_0_DSPR_Core2
  {
    mau = 8;
    type = ram;
    size = 98304; /* 96 KiB */
    map (dest=bus:local_bus, dest_offset = 0x50000000, size = 98304);
  }
  memory RegionBlock_0_DSPR_Core1
  {
    mau = 8;
    type = ram;
    size = 245760; /* 240 KiB */
    map (dest=bus:local_bus, dest_offset = 0x60000000, size = 245760);
  }
  memory RegionBlock_0_DSPR_Core0
  {
    mau = 8;
    type = ram;
    size = 245760; /* 240 KiB */
    map (dest=bus:local_bus, dest_offset = 0x70000000, size = 245760);
  }
  memory RegionBlock_Startup_Cached
  {
    mau = 8;
    type = rom;
    size = 1280; /* 1 KiB */
    map (dest=bus:local_bus, dest_offset = 0x80000000, size = 1280);
  }
  memory RegionBlock_PFlash0_Cached
  {
    mau = 8;
    type = rom;
    size = 3144448; /* 3 MiB */
    map (dest=bus:local_bus, dest_offset = 0x80000500, size = 3144448);
  }
  memory RegionBlock_BMHD0
  {
    mau = 8;
    type = rom;
    size = 512; /* 512 Byte */
    map (dest=bus:local_bus, dest_offset = 0xAF400000, size = 512);
  }
}

section_layout mpe:vtc:linear
{
  group Startup_Code_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_Startup_Cached)
  {
    group Startup_Code (ordered, contiguous, fill, align = 4)
    {
      section "Startup_Code_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.brsStartup";
      }
    }
    "_Startup_Code_START" = "_lc_gb_Startup_Code";
    "_Startup_Code_END" = ("_lc_ge_Startup_Code" == 0) ? 0 : "_lc_ge_Startup_Code" - 1;
    "_Startup_Code_LIMIT" = "_lc_ge_Startup_Code";

    "_Startup_Code_ALL_START" = "_Startup_Code_START";
    "_Startup_Code_ALL_END" = "_Startup_Code_END";
    "_Startup_Code_ALL_LIMIT" = "_Startup_Code_LIMIT";
  }

  group BMHD0_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_BMHD0)
  {
    group BMHD0 (ordered, contiguous, fill, align = 4)
    {
      section "BMHD0_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.BMHD0";
      }
    }
    "_BMHD0_START" = "_lc_gb_BMHD0";
    "_BMHD0_END" = ("_lc_ge_BMHD0" == 0) ? 0 : "_lc_ge_BMHD0" - 1;
    "_BMHD0_LIMIT" = "_lc_ge_BMHD0";

    "_BMHD0_ALL_START" = "_BMHD0_START";
    "_BMHD0_ALL_END" = "_BMHD0_END";
    "_BMHD0_ALL_LIMIT" = "_BMHD0_LIMIT";
  }

  group CSA_CORE0_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core0)
  {
    group CSA_CORE0 (ordered, contiguous, fill, align = 64)
    {
      reserved "CSA_CORE0" (size = 32768);
    }
    "_CSA_CORE0_START" = "_lc_gb_CSA_CORE0";
    "_CSA_CORE0_END" = ("_lc_ge_CSA_CORE0" == 0) ? 0 : "_lc_ge_CSA_CORE0" - 1;
    "_CSA_CORE0_LIMIT" = "_lc_ge_CSA_CORE0";

    "_CSA_CORE0_ALL_START" = "_CSA_CORE0_START";
    "_CSA_CORE0_ALL_END" = "_CSA_CORE0_END";
    "_CSA_CORE0_ALL_LIMIT" = "_CSA_CORE0_LIMIT";
  }

  group CSA_CORE1_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core1)
  {
    group CSA_CORE1 (ordered, contiguous, fill, align = 64)
    {
      reserved "CSA_CORE1" (size = 8192);
    }
    "_CSA_CORE1_START" = "_lc_gb_CSA_CORE1";
    "_CSA_CORE1_END" = ("_lc_ge_CSA_CORE1" == 0) ? 0 : "_lc_ge_CSA_CORE1" - 1;
    "_CSA_CORE1_LIMIT" = "_lc_ge_CSA_CORE1";

    "_CSA_CORE1_ALL_START" = "_CSA_CORE1_START";
    "_CSA_CORE1_ALL_END" = "_CSA_CORE1_END";
    "_CSA_CORE1_ALL_LIMIT" = "_CSA_CORE1_LIMIT";
  }

  group CSA_CORE2_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core2)
  {
    group CSA_CORE2 (ordered, contiguous, fill, align = 64)
    {
      reserved "CSA_CORE2" (size = 8192);
    }
    "_CSA_CORE2_START" = "_lc_gb_CSA_CORE2";
    "_CSA_CORE2_END" = ("_lc_ge_CSA_CORE2" == 0) ? 0 : "_lc_ge_CSA_CORE2" - 1;
    "_CSA_CORE2_LIMIT" = "_lc_ge_CSA_CORE2";

    "_CSA_CORE2_ALL_START" = "_CSA_CORE2_START";
    "_CSA_CORE2_ALL_END" = "_CSA_CORE2_END";
    "_CSA_CORE2_ALL_LIMIT" = "_CSA_CORE2_LIMIT";
  }

  group CSA_CORE3_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core3)
  {
    group CSA_CORE3 (ordered, contiguous, fill, align = 64)
    {
      reserved "CSA_CORE3" (size = 8192);
    }
    "_CSA_CORE3_START" = "_lc_gb_CSA_CORE3";
    "_CSA_CORE3_END" = ("_lc_ge_CSA_CORE3" == 0) ? 0 : "_lc_ge_CSA_CORE3" - 1;
    "_CSA_CORE3_LIMIT" = "_lc_ge_CSA_CORE3";

    "_CSA_CORE3_ALL_START" = "_CSA_CORE3_START";
    "_CSA_CORE3_ALL_END" = "_CSA_CORE3_END";
    "_CSA_CORE3_ALL_LIMIT" = "_CSA_CORE3_LIMIT";
  }

  group CSA_CORE4_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core4)
  {
    group CSA_CORE4 (ordered, contiguous, fill, align = 64)
    {
      reserved "CSA_CORE4" (size = 8192);
    }
    "_CSA_CORE4_START" = "_lc_gb_CSA_CORE4";
    "_CSA_CORE4_END" = ("_lc_ge_CSA_CORE4" == 0) ? 0 : "_lc_ge_CSA_CORE4" - 1;
    "_CSA_CORE4_LIMIT" = "_lc_ge_CSA_CORE4";

    "_CSA_CORE4_ALL_START" = "_CSA_CORE4_START";
    "_CSA_CORE4_ALL_END" = "_CSA_CORE4_END";
    "_CSA_CORE4_ALL_LIMIT" = "_CSA_CORE4_LIMIT";
  }

  group CSA_CORE5_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core5)
  {
    group CSA_CORE5 (ordered, contiguous, fill, align = 64)
    {
      reserved "CSA_CORE5" (size = 8192);
    }
    "_CSA_CORE5_START" = "_lc_gb_CSA_CORE5";
    "_CSA_CORE5_END" = ("_lc_ge_CSA_CORE5" == 0) ? 0 : "_lc_ge_CSA_CORE5" - 1;
    "_CSA_CORE5_LIMIT" = "_lc_ge_CSA_CORE5";

    "_CSA_CORE5_ALL_START" = "_CSA_CORE5_START";
    "_CSA_CORE5_ALL_END" = "_CSA_CORE5_END";
    "_CSA_CORE5_ALL_LIMIT" = "_CSA_CORE5_LIMIT";
  }

  "__CSA_BEGIN_CPU0_" = "_CSA_CORE0_START";
  "__CSA_END_CPU4_" = "_CSA_CORE4_LIMIT";
  "__CSA_BEGIN_CPU5_" = "_CSA_CORE5_START";
  "__CSA_END_CPU5_" = "_CSA_CORE5_LIMIT";
  "__CSA_END_CPU0_" = "_CSA_CORE0_LIMIT";
  "__CSA_BEGIN_CPU1_" = "_CSA_CORE1_START";
  "__CSA_END_CPU1_" = "_CSA_CORE1_LIMIT";
  "__CSA_BEGIN_CPU2_" = "_CSA_CORE2_START";
  "__CSA_END_CPU2_" = "_CSA_CORE2_LIMIT";
  "__CSA_BEGIN_CPU3_" = "_CSA_CORE3_START";
  "__CSA_END_CPU3_" = "_CSA_CORE3_LIMIT";
  "__CSA_BEGIN_CPU4_" = "_CSA_CORE4_START";

  group OS_DATA_CORE0_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_DATA_CORE0_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_CORE0_VAR_FAST";
          select "[.]zdata.OS_CORE0_VAR_FAST_NOCACHE";
          select "[.]zdata.OS_SystemApplication_OsCore0_VAR_FAST";
          select "[.]zdata.OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE0_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_INIT_ROM";
    "_OS_DATA_CORE0_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE0_VAR_FAST_INIT_ROM";

    group OS_DATA_CORE0_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_CORE0_VAR";
          select "[.]data.OS_CORE0_VAR_NOCACHE";
          select "[.]data.OS_SystemApplication_OsCore0_VAR";
          select "[.]data.OS_SystemApplication_OsCore0_VAR_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE0_VAR_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE0_VAR_INIT_ROM";
    "_OS_DATA_CORE0_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE0_VAR_INIT_ROM";

  }

  group OS_DATA_CORE0_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core0)
  {
    group OS_DATA_CORE0_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_CORE0_VAR_FAST";
        select "[.]zdata.OS_CORE0_VAR_FAST_NOCACHE";
        select "[.]zdata.OS_SystemApplication_OsCore0_VAR_FAST";
        select "[.]zdata.OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE";
      }
    }
    group OS_DATA_CORE0_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_FAST_INIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_INIT";
    "_OS_DATA_CORE0_VAR_FAST_INIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_FAST_INIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_INIT_PAD";

    group OS_DATA_CORE0_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_CORE0_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORE0_VAR_FAST_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore0_VAR_FAST_NOINIT";
      }
    }
    group OS_DATA_CORE0_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE0_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_FAST_NOINIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_NOINIT";
    "_OS_DATA_CORE0_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_NOINIT_PAD";

    group OS_DATA_CORE0_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_DATA_CORE0_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT";
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_PAD";

    group OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss";
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_DATA_CORE0_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_CORE0_VAR";
        select "[.]data.OS_CORE0_VAR_NOCACHE";
        select "[.]data.OS_SystemApplication_OsCore0_VAR";
        select "[.]data.OS_SystemApplication_OsCore0_VAR_NOCACHE";
      }
    }
    group OS_DATA_CORE0_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_INIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_INIT";
    "_OS_DATA_CORE0_VAR_INIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_INIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_INIT_PAD";

    group OS_DATA_CORE0_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_CORE0_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORE0_VAR_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore0_VAR_NOINIT";
      }
    }
    group OS_DATA_CORE0_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE0_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_NOINIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_NOINIT";
    "_OS_DATA_CORE0_VAR_NOINIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_NOINIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_NOINIT_PAD";

    group OS_DATA_CORE0_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore0_VAR_ZERO_INIT";
      }
    }
    group OS_DATA_CORE0_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT";
    "_OS_DATA_CORE0_VAR_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_PAD";

    group OS_DATA_CORE0_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE0_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_bss";
    "_OS_DATA_CORE0_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE0_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_bss_PAD";

    "_OS_DATA_CORE0_VAR_ALL_START" = "_OS_DATA_CORE0_VAR_FAST_INIT_START";
    "_OS_DATA_CORE0_VAR_ALL_END" = "_OS_DATA_CORE0_VAR_ZERO_INIT_bss_END";
    "_OS_DATA_CORE0_VAR_ALL_LIMIT" = "_OS_DATA_CORE0_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_DATA_CORE1_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_DATA_CORE1_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE1_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_CORE1_VAR_FAST";
          select "[.]zdata.OS_CORE1_VAR_FAST_NOCACHE";
          select "[.]zdata.OS_SystemApplication_OsCore1_VAR_FAST";
          select "[.]zdata.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE1_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE1_VAR_FAST_INIT_ROM";
    "_OS_DATA_CORE1_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE1_VAR_FAST_INIT_ROM";

    group OS_DATA_CORE1_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE1_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_CORE1_VAR";
          select "[.]data.OS_CORE1_VAR_NOCACHE";
          select "[.]data.OS_SystemApplication_OsCore1_VAR";
          select "[.]data.OS_SystemApplication_OsCore1_VAR_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE1_VAR_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE1_VAR_INIT_ROM";
    "_OS_DATA_CORE1_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE1_VAR_INIT_ROM";

  }

  group OS_DATA_CORE1_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core1)
  {
    group OS_DATA_CORE1_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE1_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_CORE1_VAR_FAST";
        select "[.]zdata.OS_CORE1_VAR_FAST_NOCACHE";
        select "[.]zdata.OS_SystemApplication_OsCore1_VAR_FAST";
        select "[.]zdata.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE";
      }
    }
    group OS_DATA_CORE1_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE1_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE1_VAR_FAST_INIT_START" = "_lc_gb_OS_DATA_CORE1_VAR_FAST_INIT";
    "_OS_DATA_CORE1_VAR_FAST_INIT_END" = ("_lc_gb_OS_DATA_CORE1_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE1_VAR_FAST_INIT_PAD" - 1;
    "_OS_DATA_CORE1_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE1_VAR_FAST_INIT_PAD";

    group OS_DATA_CORE1_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE1_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_CORE1_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORE1_VAR_FAST_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore1_VAR_FAST_NOINIT";
      }
    }
    group OS_DATA_CORE1_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE1_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_DATA_CORE1_VAR_FAST_NOINIT";
    "_OS_DATA_CORE1_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_DATA_CORE1_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE1_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_DATA_CORE1_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE1_VAR_FAST_NOINIT_PAD";

    group OS_DATA_CORE1_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE1_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_DATA_CORE1_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE1_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE1_VAR_FAST_ZERO_INIT";
    "_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_PAD";

    group OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss";
    "_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE1_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_DATA_CORE1_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE1_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_CORE1_VAR";
        select "[.]data.OS_CORE1_VAR_NOCACHE";
        select "[.]data.OS_SystemApplication_OsCore1_VAR";
        select "[.]data.OS_SystemApplication_OsCore1_VAR_NOCACHE";
      }
    }
    group OS_DATA_CORE1_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE1_VAR_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE1_VAR_INIT_START" = "_lc_gb_OS_DATA_CORE1_VAR_INIT";
    "_OS_DATA_CORE1_VAR_INIT_END" = ("_lc_gb_OS_DATA_CORE1_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE1_VAR_INIT_PAD" - 1;
    "_OS_DATA_CORE1_VAR_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE1_VAR_INIT_PAD";

    group OS_DATA_CORE1_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE1_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_CORE1_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORE1_VAR_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore1_VAR_NOINIT";
      }
    }
    group OS_DATA_CORE1_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE1_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE1_VAR_NOINIT_START" = "_lc_gb_OS_DATA_CORE1_VAR_NOINIT";
    "_OS_DATA_CORE1_VAR_NOINIT_END" = ("_lc_gb_OS_DATA_CORE1_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE1_VAR_NOINIT_PAD" - 1;
    "_OS_DATA_CORE1_VAR_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE1_VAR_NOINIT_PAD";

    group OS_DATA_CORE1_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE1_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore1_VAR_ZERO_INIT";
      }
    }
    group OS_DATA_CORE1_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE1_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE1_VAR_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE1_VAR_ZERO_INIT";
    "_OS_DATA_CORE1_VAR_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE1_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE1_VAR_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE1_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE1_VAR_ZERO_INIT_PAD";

    group OS_DATA_CORE1_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE1_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE1_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE1_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE1_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE1_VAR_ZERO_INIT_bss";
    "_OS_DATA_CORE1_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE1_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE1_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE1_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE1_VAR_ZERO_INIT_bss_PAD";

    "_OS_DATA_CORE1_VAR_ALL_START" = "_OS_DATA_CORE1_VAR_FAST_INIT_START";
    "_OS_DATA_CORE1_VAR_ALL_END" = "_OS_DATA_CORE1_VAR_ZERO_INIT_bss_END";
    "_OS_DATA_CORE1_VAR_ALL_LIMIT" = "_OS_DATA_CORE1_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_DATA_CORE2_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_DATA_CORE2_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE2_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_CORE2_VAR_FAST";
          select "[.]zdata.OS_CORE2_VAR_FAST_NOCACHE";
          select "[.]zdata.OS_SystemApplication_OsCore2_VAR_FAST";
          select "[.]zdata.OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE2_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE2_VAR_FAST_INIT_ROM";
    "_OS_DATA_CORE2_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE2_VAR_FAST_INIT_ROM";

    group OS_DATA_CORE2_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE2_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_CORE2_VAR";
          select "[.]data.OS_CORE2_VAR_NOCACHE";
          select "[.]data.OS_SystemApplication_OsCore2_VAR";
          select "[.]data.OS_SystemApplication_OsCore2_VAR_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE2_VAR_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE2_VAR_INIT_ROM";
    "_OS_DATA_CORE2_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE2_VAR_INIT_ROM";

  }

  group OS_DATA_CORE2_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core2)
  {
    group OS_DATA_CORE2_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE2_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_CORE2_VAR_FAST";
        select "[.]zdata.OS_CORE2_VAR_FAST_NOCACHE";
        select "[.]zdata.OS_SystemApplication_OsCore2_VAR_FAST";
        select "[.]zdata.OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE";
      }
    }
    group OS_DATA_CORE2_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE2_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE2_VAR_FAST_INIT_START" = "_lc_gb_OS_DATA_CORE2_VAR_FAST_INIT";
    "_OS_DATA_CORE2_VAR_FAST_INIT_END" = ("_lc_gb_OS_DATA_CORE2_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE2_VAR_FAST_INIT_PAD" - 1;
    "_OS_DATA_CORE2_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE2_VAR_FAST_INIT_PAD";

    group OS_DATA_CORE2_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE2_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_CORE2_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORE2_VAR_FAST_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore2_VAR_FAST_NOINIT";
      }
    }
    group OS_DATA_CORE2_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE2_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE2_VAR_FAST_NOINIT_START" = "_lc_gb_OS_DATA_CORE2_VAR_FAST_NOINIT";
    "_OS_DATA_CORE2_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_DATA_CORE2_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE2_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_DATA_CORE2_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE2_VAR_FAST_NOINIT_PAD";

    group OS_DATA_CORE2_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE2_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_DATA_CORE2_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE2_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE2_VAR_FAST_ZERO_INIT";
    "_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_PAD";

    group OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss";
    "_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE2_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_DATA_CORE2_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE2_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_CORE2_VAR";
        select "[.]data.OS_CORE2_VAR_NOCACHE";
        select "[.]data.OS_SystemApplication_OsCore2_VAR";
        select "[.]data.OS_SystemApplication_OsCore2_VAR_NOCACHE";
      }
    }
    group OS_DATA_CORE2_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE2_VAR_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE2_VAR_INIT_START" = "_lc_gb_OS_DATA_CORE2_VAR_INIT";
    "_OS_DATA_CORE2_VAR_INIT_END" = ("_lc_gb_OS_DATA_CORE2_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE2_VAR_INIT_PAD" - 1;
    "_OS_DATA_CORE2_VAR_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE2_VAR_INIT_PAD";

    group OS_DATA_CORE2_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE2_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_CORE2_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORE2_VAR_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore2_VAR_NOINIT";
      }
    }
    group OS_DATA_CORE2_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE2_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE2_VAR_NOINIT_START" = "_lc_gb_OS_DATA_CORE2_VAR_NOINIT";
    "_OS_DATA_CORE2_VAR_NOINIT_END" = ("_lc_gb_OS_DATA_CORE2_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE2_VAR_NOINIT_PAD" - 1;
    "_OS_DATA_CORE2_VAR_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE2_VAR_NOINIT_PAD";

    group OS_DATA_CORE2_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE2_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore2_VAR_ZERO_INIT";
      }
    }
    group OS_DATA_CORE2_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE2_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE2_VAR_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE2_VAR_ZERO_INIT";
    "_OS_DATA_CORE2_VAR_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE2_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE2_VAR_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE2_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE2_VAR_ZERO_INIT_PAD";

    group OS_DATA_CORE2_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE2_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE2_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE2_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE2_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE2_VAR_ZERO_INIT_bss";
    "_OS_DATA_CORE2_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE2_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE2_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE2_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE2_VAR_ZERO_INIT_bss_PAD";

    "_OS_DATA_CORE2_VAR_ALL_START" = "_OS_DATA_CORE2_VAR_FAST_INIT_START";
    "_OS_DATA_CORE2_VAR_ALL_END" = "_OS_DATA_CORE2_VAR_ZERO_INIT_bss_END";
    "_OS_DATA_CORE2_VAR_ALL_LIMIT" = "_OS_DATA_CORE2_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_DATA_CORE3_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_DATA_CORE3_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE3_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_CORE3_VAR_FAST";
          select "[.]zdata.OS_CORE3_VAR_FAST_NOCACHE";
          select "[.]zdata.OS_SystemApplication_OsCore3_VAR_FAST";
          select "[.]zdata.OS_SystemApplication_OsCore3_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE3_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE3_VAR_FAST_INIT_ROM";
    "_OS_DATA_CORE3_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE3_VAR_FAST_INIT_ROM";

    group OS_DATA_CORE3_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE3_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_CORE3_VAR";
          select "[.]data.OS_CORE3_VAR_NOCACHE";
          select "[.]data.OS_SystemApplication_OsCore3_VAR";
          select "[.]data.OS_SystemApplication_OsCore3_VAR_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE3_VAR_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE3_VAR_INIT_ROM";
    "_OS_DATA_CORE3_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE3_VAR_INIT_ROM";

  }

  group OS_DATA_CORE3_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core3)
  {
    group OS_DATA_CORE3_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE3_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_CORE3_VAR_FAST";
        select "[.]zdata.OS_CORE3_VAR_FAST_NOCACHE";
        select "[.]zdata.OS_SystemApplication_OsCore3_VAR_FAST";
        select "[.]zdata.OS_SystemApplication_OsCore3_VAR_FAST_NOCACHE";
      }
    }
    group OS_DATA_CORE3_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE3_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE3_VAR_FAST_INIT_START" = "_lc_gb_OS_DATA_CORE3_VAR_FAST_INIT";
    "_OS_DATA_CORE3_VAR_FAST_INIT_END" = ("_lc_gb_OS_DATA_CORE3_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE3_VAR_FAST_INIT_PAD" - 1;
    "_OS_DATA_CORE3_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE3_VAR_FAST_INIT_PAD";

    group OS_DATA_CORE3_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE3_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_CORE3_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORE3_VAR_FAST_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore3_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore3_VAR_FAST_NOINIT";
      }
    }
    group OS_DATA_CORE3_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE3_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE3_VAR_FAST_NOINIT_START" = "_lc_gb_OS_DATA_CORE3_VAR_FAST_NOINIT";
    "_OS_DATA_CORE3_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_DATA_CORE3_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE3_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_DATA_CORE3_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE3_VAR_FAST_NOINIT_PAD";

    group OS_DATA_CORE3_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE3_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore3_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore3_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_DATA_CORE3_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE3_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE3_VAR_FAST_ZERO_INIT";
    "_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_PAD";

    group OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore3_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore3_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss";
    "_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE3_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_DATA_CORE3_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE3_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_CORE3_VAR";
        select "[.]data.OS_CORE3_VAR_NOCACHE";
        select "[.]data.OS_SystemApplication_OsCore3_VAR";
        select "[.]data.OS_SystemApplication_OsCore3_VAR_NOCACHE";
      }
    }
    group OS_DATA_CORE3_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE3_VAR_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE3_VAR_INIT_START" = "_lc_gb_OS_DATA_CORE3_VAR_INIT";
    "_OS_DATA_CORE3_VAR_INIT_END" = ("_lc_gb_OS_DATA_CORE3_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE3_VAR_INIT_PAD" - 1;
    "_OS_DATA_CORE3_VAR_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE3_VAR_INIT_PAD";

    group OS_DATA_CORE3_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE3_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_CORE3_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORE3_VAR_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore3_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore3_VAR_NOINIT";
      }
    }
    group OS_DATA_CORE3_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE3_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE3_VAR_NOINIT_START" = "_lc_gb_OS_DATA_CORE3_VAR_NOINIT";
    "_OS_DATA_CORE3_VAR_NOINIT_END" = ("_lc_gb_OS_DATA_CORE3_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE3_VAR_NOINIT_PAD" - 1;
    "_OS_DATA_CORE3_VAR_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE3_VAR_NOINIT_PAD";

    group OS_DATA_CORE3_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE3_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore3_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore3_VAR_ZERO_INIT";
      }
    }
    group OS_DATA_CORE3_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE3_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE3_VAR_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE3_VAR_ZERO_INIT";
    "_OS_DATA_CORE3_VAR_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE3_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE3_VAR_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE3_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE3_VAR_ZERO_INIT_PAD";

    group OS_DATA_CORE3_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE3_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore3_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore3_VAR_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE3_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE3_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE3_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE3_VAR_ZERO_INIT_bss";
    "_OS_DATA_CORE3_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE3_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE3_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE3_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE3_VAR_ZERO_INIT_bss_PAD";

    "_OS_DATA_CORE3_VAR_ALL_START" = "_OS_DATA_CORE3_VAR_FAST_INIT_START";
    "_OS_DATA_CORE3_VAR_ALL_END" = "_OS_DATA_CORE3_VAR_ZERO_INIT_bss_END";
    "_OS_DATA_CORE3_VAR_ALL_LIMIT" = "_OS_DATA_CORE3_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_DATA_CORE4_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_DATA_CORE4_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE4_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_CORE4_VAR_FAST";
          select "[.]zdata.OS_CORE4_VAR_FAST_NOCACHE";
          select "[.]zdata.OS_SystemApplication_OsCore4_VAR_FAST";
          select "[.]zdata.OS_SystemApplication_OsCore4_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE4_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE4_VAR_FAST_INIT_ROM";
    "_OS_DATA_CORE4_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE4_VAR_FAST_INIT_ROM";

    group OS_DATA_CORE4_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE4_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_CORE4_VAR";
          select "[.]data.OS_CORE4_VAR_NOCACHE";
          select "[.]data.OS_SystemApplication_OsCore4_VAR";
          select "[.]data.OS_SystemApplication_OsCore4_VAR_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE4_VAR_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE4_VAR_INIT_ROM";
    "_OS_DATA_CORE4_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE4_VAR_INIT_ROM";

  }

  group OS_DATA_CORE4_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core4)
  {
    group OS_DATA_CORE4_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE4_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_CORE4_VAR_FAST";
        select "[.]zdata.OS_CORE4_VAR_FAST_NOCACHE";
        select "[.]zdata.OS_SystemApplication_OsCore4_VAR_FAST";
        select "[.]zdata.OS_SystemApplication_OsCore4_VAR_FAST_NOCACHE";
      }
    }
    group OS_DATA_CORE4_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE4_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE4_VAR_FAST_INIT_START" = "_lc_gb_OS_DATA_CORE4_VAR_FAST_INIT";
    "_OS_DATA_CORE4_VAR_FAST_INIT_END" = ("_lc_gb_OS_DATA_CORE4_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE4_VAR_FAST_INIT_PAD" - 1;
    "_OS_DATA_CORE4_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE4_VAR_FAST_INIT_PAD";

    group OS_DATA_CORE4_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE4_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_CORE4_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORE4_VAR_FAST_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore4_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore4_VAR_FAST_NOINIT";
      }
    }
    group OS_DATA_CORE4_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE4_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE4_VAR_FAST_NOINIT_START" = "_lc_gb_OS_DATA_CORE4_VAR_FAST_NOINIT";
    "_OS_DATA_CORE4_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_DATA_CORE4_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE4_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_DATA_CORE4_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE4_VAR_FAST_NOINIT_PAD";

    group OS_DATA_CORE4_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE4_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore4_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore4_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_DATA_CORE4_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE4_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE4_VAR_FAST_ZERO_INIT";
    "_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_PAD";

    group OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore4_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore4_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss";
    "_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE4_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_DATA_CORE4_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE4_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_CORE4_VAR";
        select "[.]data.OS_CORE4_VAR_NOCACHE";
        select "[.]data.OS_SystemApplication_OsCore4_VAR";
        select "[.]data.OS_SystemApplication_OsCore4_VAR_NOCACHE";
      }
    }
    group OS_DATA_CORE4_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE4_VAR_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE4_VAR_INIT_START" = "_lc_gb_OS_DATA_CORE4_VAR_INIT";
    "_OS_DATA_CORE4_VAR_INIT_END" = ("_lc_gb_OS_DATA_CORE4_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE4_VAR_INIT_PAD" - 1;
    "_OS_DATA_CORE4_VAR_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE4_VAR_INIT_PAD";

    group OS_DATA_CORE4_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE4_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_CORE4_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORE4_VAR_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore4_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore4_VAR_NOINIT";
      }
    }
    group OS_DATA_CORE4_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE4_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE4_VAR_NOINIT_START" = "_lc_gb_OS_DATA_CORE4_VAR_NOINIT";
    "_OS_DATA_CORE4_VAR_NOINIT_END" = ("_lc_gb_OS_DATA_CORE4_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE4_VAR_NOINIT_PAD" - 1;
    "_OS_DATA_CORE4_VAR_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE4_VAR_NOINIT_PAD";

    group OS_DATA_CORE4_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE4_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore4_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore4_VAR_ZERO_INIT";
      }
    }
    group OS_DATA_CORE4_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE4_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE4_VAR_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE4_VAR_ZERO_INIT";
    "_OS_DATA_CORE4_VAR_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE4_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE4_VAR_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE4_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE4_VAR_ZERO_INIT_PAD";

    group OS_DATA_CORE4_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE4_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore4_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore4_VAR_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE4_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE4_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE4_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE4_VAR_ZERO_INIT_bss";
    "_OS_DATA_CORE4_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE4_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE4_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE4_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE4_VAR_ZERO_INIT_bss_PAD";

    "_OS_DATA_CORE4_VAR_ALL_START" = "_OS_DATA_CORE4_VAR_FAST_INIT_START";
    "_OS_DATA_CORE4_VAR_ALL_END" = "_OS_DATA_CORE4_VAR_ZERO_INIT_bss_END";
    "_OS_DATA_CORE4_VAR_ALL_LIMIT" = "_OS_DATA_CORE4_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_DATA_CORE5_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_DATA_CORE5_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE5_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_CORE5_VAR_FAST";
          select "[.]zdata.OS_CORE5_VAR_FAST_NOCACHE";
          select "[.]zdata.OS_SystemApplication_OsCore5_VAR_FAST";
          select "[.]zdata.OS_SystemApplication_OsCore5_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE5_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE5_VAR_FAST_INIT_ROM";
    "_OS_DATA_CORE5_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE5_VAR_FAST_INIT_ROM";

    group OS_DATA_CORE5_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE5_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_CORE5_VAR";
          select "[.]data.OS_CORE5_VAR_NOCACHE";
          select "[.]data.OS_SystemApplication_OsCore5_VAR";
          select "[.]data.OS_SystemApplication_OsCore5_VAR_NOCACHE";
        }
      }
    }
    "_OS_DATA_CORE5_VAR_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE5_VAR_INIT_ROM";
    "_OS_DATA_CORE5_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE5_VAR_INIT_ROM";

  }

  group OS_DATA_CORE5_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core5)
  {
    group OS_DATA_CORE5_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE5_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_CORE5_VAR_FAST";
        select "[.]zdata.OS_CORE5_VAR_FAST_NOCACHE";
        select "[.]zdata.OS_SystemApplication_OsCore5_VAR_FAST";
        select "[.]zdata.OS_SystemApplication_OsCore5_VAR_FAST_NOCACHE";
      }
    }
    group OS_DATA_CORE5_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE5_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE5_VAR_FAST_INIT_START" = "_lc_gb_OS_DATA_CORE5_VAR_FAST_INIT";
    "_OS_DATA_CORE5_VAR_FAST_INIT_END" = ("_lc_gb_OS_DATA_CORE5_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE5_VAR_FAST_INIT_PAD" - 1;
    "_OS_DATA_CORE5_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE5_VAR_FAST_INIT_PAD";

    group OS_DATA_CORE5_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE5_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_CORE5_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORE5_VAR_FAST_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore5_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore5_VAR_FAST_NOINIT";
      }
    }
    group OS_DATA_CORE5_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE5_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE5_VAR_FAST_NOINIT_START" = "_lc_gb_OS_DATA_CORE5_VAR_FAST_NOINIT";
    "_OS_DATA_CORE5_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_DATA_CORE5_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE5_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_DATA_CORE5_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE5_VAR_FAST_NOINIT_PAD";

    group OS_DATA_CORE5_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE5_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore5_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore5_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_DATA_CORE5_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE5_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE5_VAR_FAST_ZERO_INIT";
    "_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_PAD";

    group OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore5_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore5_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss";
    "_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE5_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_DATA_CORE5_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE5_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_CORE5_VAR";
        select "[.]data.OS_CORE5_VAR_NOCACHE";
        select "[.]data.OS_SystemApplication_OsCore5_VAR";
        select "[.]data.OS_SystemApplication_OsCore5_VAR_NOCACHE";
      }
    }
    group OS_DATA_CORE5_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE5_VAR_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE5_VAR_INIT_START" = "_lc_gb_OS_DATA_CORE5_VAR_INIT";
    "_OS_DATA_CORE5_VAR_INIT_END" = ("_lc_gb_OS_DATA_CORE5_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE5_VAR_INIT_PAD" - 1;
    "_OS_DATA_CORE5_VAR_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE5_VAR_INIT_PAD";

    group OS_DATA_CORE5_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE5_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_CORE5_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORE5_VAR_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore5_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore5_VAR_NOINIT";
      }
    }
    group OS_DATA_CORE5_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE5_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE5_VAR_NOINIT_START" = "_lc_gb_OS_DATA_CORE5_VAR_NOINIT";
    "_OS_DATA_CORE5_VAR_NOINIT_END" = ("_lc_gb_OS_DATA_CORE5_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE5_VAR_NOINIT_PAD" - 1;
    "_OS_DATA_CORE5_VAR_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE5_VAR_NOINIT_PAD";

    group OS_DATA_CORE5_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE5_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore5_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore5_VAR_ZERO_INIT";
      }
    }
    group OS_DATA_CORE5_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE5_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE5_VAR_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE5_VAR_ZERO_INIT";
    "_OS_DATA_CORE5_VAR_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE5_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE5_VAR_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE5_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE5_VAR_ZERO_INIT_PAD";

    group OS_DATA_CORE5_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE5_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore5_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore5_VAR_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE5_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE5_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE5_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE5_VAR_ZERO_INIT_bss";
    "_OS_DATA_CORE5_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE5_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE5_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE5_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE5_VAR_ZERO_INIT_bss_PAD";

    "_OS_DATA_CORE5_VAR_ALL_START" = "_OS_DATA_CORE5_VAR_FAST_INIT_START";
    "_OS_DATA_CORE5_VAR_ALL_END" = "_OS_DATA_CORE5_VAR_ZERO_INIT_bss_END";
    "_OS_DATA_CORE5_VAR_ALL_LIMIT" = "_OS_DATA_CORE5_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_DATA_CORE6_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_DATA_CORE6_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      reserved "OS_DATA_CORE6_VAR_FAST_INIT_ROM" (size = 0);
    }
    "_OS_DATA_CORE6_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE6_VAR_FAST_INIT_ROM";
    "_OS_DATA_CORE6_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE6_VAR_FAST_INIT_ROM";

    group OS_DATA_CORE6_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      reserved "OS_DATA_CORE6_VAR_INIT_ROM" (size = 0);
    }
    "_OS_DATA_CORE6_VAR_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE6_VAR_INIT_ROM";
    "_OS_DATA_CORE6_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE6_VAR_INIT_ROM";

  }

  group OS_DATA_CORE6_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core5)
  {
    group OS_DATA_CORE6_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      reserved "OS_DATA_CORE6_VAR_FAST_INIT" (size = 0);
    }
    group OS_DATA_CORE6_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE6_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE6_VAR_FAST_INIT_START" = "_lc_gb_OS_DATA_CORE6_VAR_FAST_INIT";
    "_OS_DATA_CORE6_VAR_FAST_INIT_END" = ("_lc_gb_OS_DATA_CORE6_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE6_VAR_FAST_INIT_PAD" - 1;
    "_OS_DATA_CORE6_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE6_VAR_FAST_INIT_PAD";

    group OS_DATA_CORE6_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      reserved "OS_DATA_CORE6_VAR_FAST_NOINIT" (size = 0);
    }
    group OS_DATA_CORE6_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE6_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE6_VAR_FAST_NOINIT_START" = "_lc_gb_OS_DATA_CORE6_VAR_FAST_NOINIT";
    "_OS_DATA_CORE6_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_DATA_CORE6_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE6_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_DATA_CORE6_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE6_VAR_FAST_NOINIT_PAD";

    group OS_DATA_CORE6_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      reserved "OS_DATA_CORE6_VAR_INIT" (size = 0);
    }
    group OS_DATA_CORE6_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE6_VAR_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE6_VAR_INIT_START" = "_lc_gb_OS_DATA_CORE6_VAR_INIT";
    "_OS_DATA_CORE6_VAR_INIT_END" = ("_lc_gb_OS_DATA_CORE6_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE6_VAR_INIT_PAD" - 1;
    "_OS_DATA_CORE6_VAR_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE6_VAR_INIT_PAD";

    group OS_DATA_CORE6_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      reserved "OS_DATA_CORE6_VAR_NOINIT" (size = 0);
    }
    group OS_DATA_CORE6_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE6_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE6_VAR_NOINIT_START" = "_lc_gb_OS_DATA_CORE6_VAR_NOINIT";
    "_OS_DATA_CORE6_VAR_NOINIT_END" = ("_lc_gb_OS_DATA_CORE6_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE6_VAR_NOINIT_PAD" - 1;
    "_OS_DATA_CORE6_VAR_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE6_VAR_NOINIT_PAD";

    "_OS_DATA_CORE6_VAR_ALL_START" = "_OS_DATA_CORE6_VAR_FAST_INIT_START";
    "_OS_DATA_CORE6_VAR_ALL_END" = "_OS_DATA_CORE6_VAR_NOINIT_END";
    "_OS_DATA_CORE6_VAR_ALL_LIMIT" = "_OS_DATA_CORE6_VAR_NOINIT_LIMIT";
  }

  group OS_DATA_SHARED_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_DATA_SHARED_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_DATA_SHARED_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_DATA_SHARED_VAR_FAST_INIT_ROM";
    "_OS_DATA_SHARED_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_SHARED_VAR_FAST_INIT_ROM";

    group OS_DATA_SHARED_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_VAR_NOCACHE";
        }
      }
    }
    "_OS_DATA_SHARED_VAR_INIT_ROM_START" = "_lc_gb_OS_DATA_SHARED_VAR_INIT_ROM";
    "_OS_DATA_SHARED_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_SHARED_VAR_INIT_ROM";

  }

  group OS_DATA_SHARED_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core0)
  {
    group OS_DATA_SHARED_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_VAR_FAST_NOCACHE";
      }
    }
    group OS_DATA_SHARED_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_SHARED_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_DATA_SHARED_VAR_FAST_INIT_START" = "_lc_gb_OS_DATA_SHARED_VAR_FAST_INIT";
    "_OS_DATA_SHARED_VAR_FAST_INIT_END" = ("_lc_gb_OS_DATA_SHARED_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_SHARED_VAR_FAST_INIT_PAD" - 1;
    "_OS_DATA_SHARED_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_DATA_SHARED_VAR_FAST_INIT_PAD";

    group OS_DATA_SHARED_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_BARRIER_CORE0_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_BARRIER_CORE2_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_BARRIER_CORE3_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_BARRIER_CORE4_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_BARRIER_CORE5_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORESTATUS_CORE0_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORESTATUS_CORE2_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORESTATUS_CORE3_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORESTATUS_CORE4_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORESTATUS_CORE5_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_PUBLIC_CORE0_VAR_FAST_NOINIT";
        select "[.]zbss.OS_PUBLIC_CORE1_VAR_FAST_NOINIT";
        select "[.]zbss.OS_PUBLIC_CORE2_VAR_FAST_NOINIT";
        select "[.]zbss.OS_PUBLIC_CORE3_VAR_FAST_NOINIT";
        select "[.]zbss.OS_PUBLIC_CORE4_VAR_FAST_NOINIT";
        select "[.]zbss.OS_PUBLIC_CORE5_VAR_FAST_NOINIT";
        select "[.]zbss.OS_VAR_FAST_NOCACHE_NOINIT";
      }
    }
    group OS_DATA_SHARED_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_SHARED_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_SHARED_VAR_FAST_NOINIT_START" = "_lc_gb_OS_DATA_SHARED_VAR_FAST_NOINIT";
    "_OS_DATA_SHARED_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_DATA_SHARED_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_SHARED_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_DATA_SHARED_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_DATA_SHARED_VAR_FAST_NOINIT_PAD";

    group OS_DATA_SHARED_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_VAR_NOCACHE";
      }
    }
    group OS_DATA_SHARED_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_SHARED_VAR_INIT_PAD" (size = 16);
    }
    "_OS_DATA_SHARED_VAR_INIT_START" = "_lc_gb_OS_DATA_SHARED_VAR_INIT";
    "_OS_DATA_SHARED_VAR_INIT_END" = ("_lc_gb_OS_DATA_SHARED_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_SHARED_VAR_INIT_PAD" - 1;
    "_OS_DATA_SHARED_VAR_INIT_LIMIT" = "_lc_gb_OS_DATA_SHARED_VAR_INIT_PAD";

    group OS_DATA_SHARED_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_BARRIER_CORE0_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_BARRIER_CORE2_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_BARRIER_CORE3_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_BARRIER_CORE4_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_BARRIER_CORE5_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORESTATUS_CORE0_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORESTATUS_CORE2_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORESTATUS_CORE3_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORESTATUS_CORE4_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORESTATUS_CORE5_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_PUBLIC_CORE0_VAR_NOINIT";
        select "[.]bss.OS_PUBLIC_CORE1_VAR_NOINIT";
        select "[.]bss.OS_PUBLIC_CORE2_VAR_NOINIT";
        select "[.]bss.OS_PUBLIC_CORE3_VAR_NOINIT";
        select "[.]bss.OS_PUBLIC_CORE4_VAR_NOINIT";
        select "[.]bss.OS_PUBLIC_CORE5_VAR_NOINIT";
        select "[.]bss.OS_VAR_NOCACHE_NOINIT";
      }
    }
    group OS_DATA_SHARED_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_SHARED_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_SHARED_VAR_NOINIT_START" = "_lc_gb_OS_DATA_SHARED_VAR_NOINIT";
    "_OS_DATA_SHARED_VAR_NOINIT_END" = ("_lc_gb_OS_DATA_SHARED_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_SHARED_VAR_NOINIT_PAD" - 1;
    "_OS_DATA_SHARED_VAR_NOINIT_LIMIT" = "_lc_gb_OS_DATA_SHARED_VAR_NOINIT_PAD";

    "_OS_DATA_SHARED_VAR_ALL_START" = "_OS_DATA_SHARED_VAR_FAST_INIT_START";
    "_OS_DATA_SHARED_VAR_ALL_END" = "_OS_DATA_SHARED_VAR_NOINIT_END";
    "_OS_DATA_SHARED_VAR_ALL_LIMIT" = "_OS_DATA_SHARED_VAR_NOINIT_LIMIT";
  }

  group OS_EXCVEC_CORE0_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE0_CODE (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE0_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_EXCVEC_CORE0_CODE";
      }
    }
    group OS_EXCVEC_CORE0_CODE_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE0_CODE_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE0_CODE_START" = "_lc_gb_OS_EXCVEC_CORE0_CODE";
    "_OS_EXCVEC_CORE0_CODE_END" = ("_lc_gb_OS_EXCVEC_CORE0_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE0_CODE_PAD" - 1;
    "_OS_EXCVEC_CORE0_CODE_LIMIT" = "_lc_gb_OS_EXCVEC_CORE0_CODE_PAD";

    "_OS_EXCVEC_CORE0_CODE_ALL_START" = "_OS_EXCVEC_CORE0_CODE_START";
    "_OS_EXCVEC_CORE0_CODE_ALL_END" = "_OS_EXCVEC_CORE0_CODE_END";
    "_OS_EXCVEC_CORE0_CODE_ALL_LIMIT" = "_OS_EXCVEC_CORE0_CODE_LIMIT";
  }

  group OS_EXCVEC_CORE0_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE0_CONST (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE0_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_EXCVEC_CORE0_CONST";
      }
    }
    group OS_EXCVEC_CORE0_CONST_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE0_CONST_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE0_CONST_START" = "_lc_gb_OS_EXCVEC_CORE0_CONST";
    "_OS_EXCVEC_CORE0_CONST_END" = ("_lc_gb_OS_EXCVEC_CORE0_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE0_CONST_PAD" - 1;
    "_OS_EXCVEC_CORE0_CONST_LIMIT" = "_lc_gb_OS_EXCVEC_CORE0_CONST_PAD";

    "_OS_EXCVEC_CORE0_CONST_ALL_START" = "_OS_EXCVEC_CORE0_CONST_START";
    "_OS_EXCVEC_CORE0_CONST_ALL_END" = "_OS_EXCVEC_CORE0_CONST_END";
    "_OS_EXCVEC_CORE0_CONST_ALL_LIMIT" = "_OS_EXCVEC_CORE0_CONST_LIMIT";
  }

  group OS_EXCVEC_CORE1_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE1_CODE (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE1_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_EXCVEC_CORE1_CODE";
      }
    }
    group OS_EXCVEC_CORE1_CODE_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE1_CODE_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE1_CODE_START" = "_lc_gb_OS_EXCVEC_CORE1_CODE";
    "_OS_EXCVEC_CORE1_CODE_END" = ("_lc_gb_OS_EXCVEC_CORE1_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE1_CODE_PAD" - 1;
    "_OS_EXCVEC_CORE1_CODE_LIMIT" = "_lc_gb_OS_EXCVEC_CORE1_CODE_PAD";

    "_OS_EXCVEC_CORE1_CODE_ALL_START" = "_OS_EXCVEC_CORE1_CODE_START";
    "_OS_EXCVEC_CORE1_CODE_ALL_END" = "_OS_EXCVEC_CORE1_CODE_END";
    "_OS_EXCVEC_CORE1_CODE_ALL_LIMIT" = "_OS_EXCVEC_CORE1_CODE_LIMIT";
  }

  group OS_EXCVEC_CORE1_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE1_CONST (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE1_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_EXCVEC_CORE1_CONST";
      }
    }
    group OS_EXCVEC_CORE1_CONST_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE1_CONST_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE1_CONST_START" = "_lc_gb_OS_EXCVEC_CORE1_CONST";
    "_OS_EXCVEC_CORE1_CONST_END" = ("_lc_gb_OS_EXCVEC_CORE1_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE1_CONST_PAD" - 1;
    "_OS_EXCVEC_CORE1_CONST_LIMIT" = "_lc_gb_OS_EXCVEC_CORE1_CONST_PAD";

    "_OS_EXCVEC_CORE1_CONST_ALL_START" = "_OS_EXCVEC_CORE1_CONST_START";
    "_OS_EXCVEC_CORE1_CONST_ALL_END" = "_OS_EXCVEC_CORE1_CONST_END";
    "_OS_EXCVEC_CORE1_CONST_ALL_LIMIT" = "_OS_EXCVEC_CORE1_CONST_LIMIT";
  }

  group OS_EXCVEC_CORE2_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE2_CODE (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE2_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_EXCVEC_CORE2_CODE";
      }
    }
    group OS_EXCVEC_CORE2_CODE_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE2_CODE_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE2_CODE_START" = "_lc_gb_OS_EXCVEC_CORE2_CODE";
    "_OS_EXCVEC_CORE2_CODE_END" = ("_lc_gb_OS_EXCVEC_CORE2_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE2_CODE_PAD" - 1;
    "_OS_EXCVEC_CORE2_CODE_LIMIT" = "_lc_gb_OS_EXCVEC_CORE2_CODE_PAD";

    "_OS_EXCVEC_CORE2_CODE_ALL_START" = "_OS_EXCVEC_CORE2_CODE_START";
    "_OS_EXCVEC_CORE2_CODE_ALL_END" = "_OS_EXCVEC_CORE2_CODE_END";
    "_OS_EXCVEC_CORE2_CODE_ALL_LIMIT" = "_OS_EXCVEC_CORE2_CODE_LIMIT";
  }

  group OS_EXCVEC_CORE2_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE2_CONST (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE2_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_EXCVEC_CORE2_CONST";
      }
    }
    group OS_EXCVEC_CORE2_CONST_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE2_CONST_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE2_CONST_START" = "_lc_gb_OS_EXCVEC_CORE2_CONST";
    "_OS_EXCVEC_CORE2_CONST_END" = ("_lc_gb_OS_EXCVEC_CORE2_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE2_CONST_PAD" - 1;
    "_OS_EXCVEC_CORE2_CONST_LIMIT" = "_lc_gb_OS_EXCVEC_CORE2_CONST_PAD";

    "_OS_EXCVEC_CORE2_CONST_ALL_START" = "_OS_EXCVEC_CORE2_CONST_START";
    "_OS_EXCVEC_CORE2_CONST_ALL_END" = "_OS_EXCVEC_CORE2_CONST_END";
    "_OS_EXCVEC_CORE2_CONST_ALL_LIMIT" = "_OS_EXCVEC_CORE2_CONST_LIMIT";
  }

  group OS_EXCVEC_CORE3_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE3_CODE (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE3_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_EXCVEC_CORE3_CODE";
      }
    }
    group OS_EXCVEC_CORE3_CODE_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE3_CODE_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE3_CODE_START" = "_lc_gb_OS_EXCVEC_CORE3_CODE";
    "_OS_EXCVEC_CORE3_CODE_END" = ("_lc_gb_OS_EXCVEC_CORE3_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE3_CODE_PAD" - 1;
    "_OS_EXCVEC_CORE3_CODE_LIMIT" = "_lc_gb_OS_EXCVEC_CORE3_CODE_PAD";

    "_OS_EXCVEC_CORE3_CODE_ALL_START" = "_OS_EXCVEC_CORE3_CODE_START";
    "_OS_EXCVEC_CORE3_CODE_ALL_END" = "_OS_EXCVEC_CORE3_CODE_END";
    "_OS_EXCVEC_CORE3_CODE_ALL_LIMIT" = "_OS_EXCVEC_CORE3_CODE_LIMIT";
  }

  group OS_EXCVEC_CORE3_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE3_CONST (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE3_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_EXCVEC_CORE3_CONST";
      }
    }
    group OS_EXCVEC_CORE3_CONST_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE3_CONST_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE3_CONST_START" = "_lc_gb_OS_EXCVEC_CORE3_CONST";
    "_OS_EXCVEC_CORE3_CONST_END" = ("_lc_gb_OS_EXCVEC_CORE3_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE3_CONST_PAD" - 1;
    "_OS_EXCVEC_CORE3_CONST_LIMIT" = "_lc_gb_OS_EXCVEC_CORE3_CONST_PAD";

    "_OS_EXCVEC_CORE3_CONST_ALL_START" = "_OS_EXCVEC_CORE3_CONST_START";
    "_OS_EXCVEC_CORE3_CONST_ALL_END" = "_OS_EXCVEC_CORE3_CONST_END";
    "_OS_EXCVEC_CORE3_CONST_ALL_LIMIT" = "_OS_EXCVEC_CORE3_CONST_LIMIT";
  }

  group OS_EXCVEC_CORE4_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE4_CODE (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE4_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_EXCVEC_CORE4_CODE";
      }
    }
    group OS_EXCVEC_CORE4_CODE_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE4_CODE_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE4_CODE_START" = "_lc_gb_OS_EXCVEC_CORE4_CODE";
    "_OS_EXCVEC_CORE4_CODE_END" = ("_lc_gb_OS_EXCVEC_CORE4_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE4_CODE_PAD" - 1;
    "_OS_EXCVEC_CORE4_CODE_LIMIT" = "_lc_gb_OS_EXCVEC_CORE4_CODE_PAD";

    "_OS_EXCVEC_CORE4_CODE_ALL_START" = "_OS_EXCVEC_CORE4_CODE_START";
    "_OS_EXCVEC_CORE4_CODE_ALL_END" = "_OS_EXCVEC_CORE4_CODE_END";
    "_OS_EXCVEC_CORE4_CODE_ALL_LIMIT" = "_OS_EXCVEC_CORE4_CODE_LIMIT";
  }

  group OS_EXCVEC_CORE4_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE4_CONST (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE4_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_EXCVEC_CORE4_CONST";
      }
    }
    group OS_EXCVEC_CORE4_CONST_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE4_CONST_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE4_CONST_START" = "_lc_gb_OS_EXCVEC_CORE4_CONST";
    "_OS_EXCVEC_CORE4_CONST_END" = ("_lc_gb_OS_EXCVEC_CORE4_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE4_CONST_PAD" - 1;
    "_OS_EXCVEC_CORE4_CONST_LIMIT" = "_lc_gb_OS_EXCVEC_CORE4_CONST_PAD";

    "_OS_EXCVEC_CORE4_CONST_ALL_START" = "_OS_EXCVEC_CORE4_CONST_START";
    "_OS_EXCVEC_CORE4_CONST_ALL_END" = "_OS_EXCVEC_CORE4_CONST_END";
    "_OS_EXCVEC_CORE4_CONST_ALL_LIMIT" = "_OS_EXCVEC_CORE4_CONST_LIMIT";
  }

  group OS_EXCVEC_CORE5_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE5_CODE (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE5_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_EXCVEC_CORE5_CODE";
      }
    }
    group OS_EXCVEC_CORE5_CODE_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE5_CODE_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE5_CODE_START" = "_lc_gb_OS_EXCVEC_CORE5_CODE";
    "_OS_EXCVEC_CORE5_CODE_END" = ("_lc_gb_OS_EXCVEC_CORE5_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE5_CODE_PAD" - 1;
    "_OS_EXCVEC_CORE5_CODE_LIMIT" = "_lc_gb_OS_EXCVEC_CORE5_CODE_PAD";

    "_OS_EXCVEC_CORE5_CODE_ALL_START" = "_OS_EXCVEC_CORE5_CODE_START";
    "_OS_EXCVEC_CORE5_CODE_ALL_END" = "_OS_EXCVEC_CORE5_CODE_END";
    "_OS_EXCVEC_CORE5_CODE_ALL_LIMIT" = "_OS_EXCVEC_CORE5_CODE_LIMIT";
  }

  group OS_EXCVEC_CORE5_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE5_CONST (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE5_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_EXCVEC_CORE5_CONST";
      }
    }
    group OS_EXCVEC_CORE5_CONST_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE5_CONST_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE5_CONST_START" = "_lc_gb_OS_EXCVEC_CORE5_CONST";
    "_OS_EXCVEC_CORE5_CONST_END" = ("_lc_gb_OS_EXCVEC_CORE5_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE5_CONST_PAD" - 1;
    "_OS_EXCVEC_CORE5_CONST_LIMIT" = "_lc_gb_OS_EXCVEC_CORE5_CONST_PAD";

    "_OS_EXCVEC_CORE5_CONST_ALL_START" = "_OS_EXCVEC_CORE5_CONST_START";
    "_OS_EXCVEC_CORE5_CONST_ALL_END" = "_OS_EXCVEC_CORE5_CONST_END";
    "_OS_EXCVEC_CORE5_CONST_ALL_LIMIT" = "_OS_EXCVEC_CORE5_CONST_LIMIT";
  }

  group OS_EXCVEC_CORE6_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE6_CODE (ordered, contiguous, fill, align = 256)
    {
      reserved "OS_EXCVEC_CORE6_CODE" (size = 0);
    }
    group OS_EXCVEC_CORE6_CODE_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE6_CODE_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE6_CODE_START" = "_lc_gb_OS_EXCVEC_CORE6_CODE";
    "_OS_EXCVEC_CORE6_CODE_END" = ("_lc_gb_OS_EXCVEC_CORE6_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE6_CODE_PAD" - 1;
    "_OS_EXCVEC_CORE6_CODE_LIMIT" = "_lc_gb_OS_EXCVEC_CORE6_CODE_PAD";

    "_OS_EXCVEC_CORE6_CODE_ALL_START" = "_OS_EXCVEC_CORE6_CODE_START";
    "_OS_EXCVEC_CORE6_CODE_ALL_END" = "_OS_EXCVEC_CORE6_CODE_END";
    "_OS_EXCVEC_CORE6_CODE_ALL_LIMIT" = "_OS_EXCVEC_CORE6_CODE_LIMIT";
  }

  group OS_EXCVEC_CORE6_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_EXCVEC_CORE6_CONST (ordered, contiguous, fill, align = 256)
    {
      reserved "OS_EXCVEC_CORE6_CONST" (size = 0);
    }
    group OS_EXCVEC_CORE6_CONST_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE6_CONST_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE6_CONST_START" = "_lc_gb_OS_EXCVEC_CORE6_CONST";
    "_OS_EXCVEC_CORE6_CONST_END" = ("_lc_gb_OS_EXCVEC_CORE6_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE6_CONST_PAD" - 1;
    "_OS_EXCVEC_CORE6_CONST_LIMIT" = "_lc_gb_OS_EXCVEC_CORE6_CONST_PAD";

    "_OS_EXCVEC_CORE6_CONST_ALL_START" = "_OS_EXCVEC_CORE6_CONST_START";
    "_OS_EXCVEC_CORE6_CONST_ALL_END" = "_OS_EXCVEC_CORE6_CONST_END";
    "_OS_EXCVEC_CORE6_CONST_ALL_LIMIT" = "_OS_EXCVEC_CORE6_CONST_LIMIT";
  }

  group OS_GLOBALSHARED_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_GLOBALSHARED_CONST (ordered, contiguous, fill)
    {
      section "OS_GLOBALSHARED_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_GLOBALSHARED_CONST";
        select "[.]zrodata.OS_GLOBALSHARED_CONST_FAST";
      }
    }
    group OS_GLOBALSHARED_CONST_PAD (align = 1)
    {
      reserved "OS_GLOBALSHARED_CONST_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_CONST_START" = "_lc_gb_OS_GLOBALSHARED_CONST";
    "_OS_GLOBALSHARED_CONST_END" = ("_lc_gb_OS_GLOBALSHARED_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_CONST_PAD" - 1;
    "_OS_GLOBALSHARED_CONST_LIMIT" = "_lc_gb_OS_GLOBALSHARED_CONST_PAD";

    "_OS_GLOBALSHARED_CONST_ALL_START" = "_OS_GLOBALSHARED_CONST_START";
    "_OS_GLOBALSHARED_CONST_ALL_END" = "_OS_GLOBALSHARED_CONST_END";
    "_OS_GLOBALSHARED_CONST_ALL_LIMIT" = "_OS_GLOBALSHARED_CONST_LIMIT";
  }

  group OS_GLOBALSHARED_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_GLOBALSHARED_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_GLOBALSHARED_VAR_FAST";
          select "[.]zdata.OS_GLOBALSHARED_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_GLOBALSHARED_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_INIT_ROM";
    "_OS_GLOBALSHARED_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_GLOBALSHARED_VAR_FAST_INIT_ROM";

    group OS_GLOBALSHARED_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_GLOBALSHARED_VAR";
          select "[.]data.OS_GLOBALSHARED_VAR_NOCACHE";
        }
      }
    }
    "_OS_GLOBALSHARED_VAR_INIT_ROM_START" = "_lc_gb_OS_GLOBALSHARED_VAR_INIT_ROM";
    "_OS_GLOBALSHARED_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_GLOBALSHARED_VAR_INIT_ROM";

  }

  group OS_GLOBALSHARED_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core0)
  {
    group OS_GLOBALSHARED_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_GLOBALSHARED_VAR_FAST";
        select "[.]zdata.OS_GLOBALSHARED_VAR_FAST_NOCACHE";
      }
    }
    group OS_GLOBALSHARED_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_FAST_INIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_INIT";
    "_OS_GLOBALSHARED_VAR_FAST_INIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_FAST_INIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_INIT_PAD";

    group OS_GLOBALSHARED_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_GLOBALSHARED_VAR_FAST_NOINIT";
      }
    }
    group OS_GLOBALSHARED_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_GLOBALSHARED_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_FAST_NOINIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_NOINIT";
    "_OS_GLOBALSHARED_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_NOINIT_PAD";

    group OS_GLOBALSHARED_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_GLOBALSHARED_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT";
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_PAD";

    group OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss";
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_GLOBALSHARED_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_GLOBALSHARED_VAR";
        select "[.]data.OS_GLOBALSHARED_VAR_NOCACHE";
      }
    }
    group OS_GLOBALSHARED_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_INIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_INIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_INIT";
    "_OS_GLOBALSHARED_VAR_INIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_INIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_INIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_INIT_PAD";

    group OS_GLOBALSHARED_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_GLOBALSHARED_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_GLOBALSHARED_VAR_NOINIT";
      }
    }
    group OS_GLOBALSHARED_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_GLOBALSHARED_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_NOINIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_NOINIT";
    "_OS_GLOBALSHARED_VAR_NOINIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_NOINIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_NOINIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_NOINIT_PAD";

    group OS_GLOBALSHARED_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_GLOBALSHARED_VAR_ZERO_INIT";
      }
    }
    group OS_GLOBALSHARED_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT";
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_PAD";

    group OS_GLOBALSHARED_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_GLOBALSHARED_VAR_ZERO_INIT_bss";
      }
    }
    group OS_GLOBALSHARED_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_bss";
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_PAD";

    "_OS_GLOBALSHARED_VAR_ALL_START" = "_OS_GLOBALSHARED_VAR_FAST_INIT_START";
    "_OS_GLOBALSHARED_VAR_ALL_END" = "_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_END";
    "_OS_GLOBALSHARED_VAR_ALL_LIMIT" = "_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_INTVEC_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CODE (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_INTVEC_CODE";
      }
    }
    group OS_INTVEC_CODE_PAD (align = 8)
    {
      reserved "OS_INTVEC_CODE_PAD" (size = 16);
    }
    "_OS_INTVEC_CODE_START" = "_lc_gb_OS_INTVEC_CODE";
    "_OS_INTVEC_CODE_END" = ("_lc_gb_OS_INTVEC_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CODE_PAD" - 1;
    "_OS_INTVEC_CODE_LIMIT" = "_lc_gb_OS_INTVEC_CODE_PAD";

    "_OS_INTVEC_CODE_ALL_START" = "_OS_INTVEC_CODE_START";
    "_OS_INTVEC_CODE_ALL_END" = "_OS_INTVEC_CODE_END";
    "_OS_INTVEC_CODE_ALL_LIMIT" = "_OS_INTVEC_CODE_LIMIT";
  }

  group OS_INTVEC_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CONST (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_INTVEC_CONST";
      }
    }
    group OS_INTVEC_CONST_PAD (align = 8)
    {
      reserved "OS_INTVEC_CONST_PAD" (size = 16);
    }
    "_OS_INTVEC_CONST_START" = "_lc_gb_OS_INTVEC_CONST";
    "_OS_INTVEC_CONST_END" = ("_lc_gb_OS_INTVEC_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CONST_PAD" - 1;
    "_OS_INTVEC_CONST_LIMIT" = "_lc_gb_OS_INTVEC_CONST_PAD";

    "_OS_INTVEC_CONST_ALL_START" = "_OS_INTVEC_CONST_START";
    "_OS_INTVEC_CONST_ALL_END" = "_OS_INTVEC_CONST_END";
    "_OS_INTVEC_CONST_ALL_LIMIT" = "_OS_INTVEC_CONST_LIMIT";
  }

  group OS_INTVEC_CORE0_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE0_CODE (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE0_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_INTVEC_CORE0_CODE";
      }
    }
    group OS_INTVEC_CORE0_CODE_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE0_CODE_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE0_CODE_START" = "_lc_gb_OS_INTVEC_CORE0_CODE";
    "_OS_INTVEC_CORE0_CODE_END" = ("_lc_gb_OS_INTVEC_CORE0_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE0_CODE_PAD" - 1;
    "_OS_INTVEC_CORE0_CODE_LIMIT" = "_lc_gb_OS_INTVEC_CORE0_CODE_PAD";

    "_OS_INTVEC_CORE0_CODE_ALL_START" = "_OS_INTVEC_CORE0_CODE_START";
    "_OS_INTVEC_CORE0_CODE_ALL_END" = "_OS_INTVEC_CORE0_CODE_END";
    "_OS_INTVEC_CORE0_CODE_ALL_LIMIT" = "_OS_INTVEC_CORE0_CODE_LIMIT";
  }

  group OS_INTVEC_CORE0_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE0_CONST (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE0_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_INTVEC_CORE0_CONST";
      }
    }
    group OS_INTVEC_CORE0_CONST_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE0_CONST_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE0_CONST_START" = "_lc_gb_OS_INTVEC_CORE0_CONST";
    "_OS_INTVEC_CORE0_CONST_END" = ("_lc_gb_OS_INTVEC_CORE0_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE0_CONST_PAD" - 1;
    "_OS_INTVEC_CORE0_CONST_LIMIT" = "_lc_gb_OS_INTVEC_CORE0_CONST_PAD";

    "_OS_INTVEC_CORE0_CONST_ALL_START" = "_OS_INTVEC_CORE0_CONST_START";
    "_OS_INTVEC_CORE0_CONST_ALL_END" = "_OS_INTVEC_CORE0_CONST_END";
    "_OS_INTVEC_CORE0_CONST_ALL_LIMIT" = "_OS_INTVEC_CORE0_CONST_LIMIT";
  }

  group OS_INTVEC_CORE1_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE1_CODE (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE1_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_INTVEC_CORE1_CODE";
      }
    }
    group OS_INTVEC_CORE1_CODE_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE1_CODE_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE1_CODE_START" = "_lc_gb_OS_INTVEC_CORE1_CODE";
    "_OS_INTVEC_CORE1_CODE_END" = ("_lc_gb_OS_INTVEC_CORE1_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE1_CODE_PAD" - 1;
    "_OS_INTVEC_CORE1_CODE_LIMIT" = "_lc_gb_OS_INTVEC_CORE1_CODE_PAD";

    "_OS_INTVEC_CORE1_CODE_ALL_START" = "_OS_INTVEC_CORE1_CODE_START";
    "_OS_INTVEC_CORE1_CODE_ALL_END" = "_OS_INTVEC_CORE1_CODE_END";
    "_OS_INTVEC_CORE1_CODE_ALL_LIMIT" = "_OS_INTVEC_CORE1_CODE_LIMIT";
  }

  group OS_INTVEC_CORE1_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE1_CONST (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE1_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_INTVEC_CORE1_CONST";
      }
    }
    group OS_INTVEC_CORE1_CONST_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE1_CONST_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE1_CONST_START" = "_lc_gb_OS_INTVEC_CORE1_CONST";
    "_OS_INTVEC_CORE1_CONST_END" = ("_lc_gb_OS_INTVEC_CORE1_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE1_CONST_PAD" - 1;
    "_OS_INTVEC_CORE1_CONST_LIMIT" = "_lc_gb_OS_INTVEC_CORE1_CONST_PAD";

    "_OS_INTVEC_CORE1_CONST_ALL_START" = "_OS_INTVEC_CORE1_CONST_START";
    "_OS_INTVEC_CORE1_CONST_ALL_END" = "_OS_INTVEC_CORE1_CONST_END";
    "_OS_INTVEC_CORE1_CONST_ALL_LIMIT" = "_OS_INTVEC_CORE1_CONST_LIMIT";
  }

  group OS_INTVEC_CORE2_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE2_CODE (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE2_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_INTVEC_CORE2_CODE";
      }
    }
    group OS_INTVEC_CORE2_CODE_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE2_CODE_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE2_CODE_START" = "_lc_gb_OS_INTVEC_CORE2_CODE";
    "_OS_INTVEC_CORE2_CODE_END" = ("_lc_gb_OS_INTVEC_CORE2_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE2_CODE_PAD" - 1;
    "_OS_INTVEC_CORE2_CODE_LIMIT" = "_lc_gb_OS_INTVEC_CORE2_CODE_PAD";

    "_OS_INTVEC_CORE2_CODE_ALL_START" = "_OS_INTVEC_CORE2_CODE_START";
    "_OS_INTVEC_CORE2_CODE_ALL_END" = "_OS_INTVEC_CORE2_CODE_END";
    "_OS_INTVEC_CORE2_CODE_ALL_LIMIT" = "_OS_INTVEC_CORE2_CODE_LIMIT";
  }

  group OS_INTVEC_CORE2_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE2_CONST (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE2_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_INTVEC_CORE2_CONST";
      }
    }
    group OS_INTVEC_CORE2_CONST_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE2_CONST_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE2_CONST_START" = "_lc_gb_OS_INTVEC_CORE2_CONST";
    "_OS_INTVEC_CORE2_CONST_END" = ("_lc_gb_OS_INTVEC_CORE2_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE2_CONST_PAD" - 1;
    "_OS_INTVEC_CORE2_CONST_LIMIT" = "_lc_gb_OS_INTVEC_CORE2_CONST_PAD";

    "_OS_INTVEC_CORE2_CONST_ALL_START" = "_OS_INTVEC_CORE2_CONST_START";
    "_OS_INTVEC_CORE2_CONST_ALL_END" = "_OS_INTVEC_CORE2_CONST_END";
    "_OS_INTVEC_CORE2_CONST_ALL_LIMIT" = "_OS_INTVEC_CORE2_CONST_LIMIT";
  }

  group OS_INTVEC_CORE3_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE3_CODE (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE3_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_INTVEC_CORE3_CODE";
      }
    }
    group OS_INTVEC_CORE3_CODE_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE3_CODE_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE3_CODE_START" = "_lc_gb_OS_INTVEC_CORE3_CODE";
    "_OS_INTVEC_CORE3_CODE_END" = ("_lc_gb_OS_INTVEC_CORE3_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE3_CODE_PAD" - 1;
    "_OS_INTVEC_CORE3_CODE_LIMIT" = "_lc_gb_OS_INTVEC_CORE3_CODE_PAD";

    "_OS_INTVEC_CORE3_CODE_ALL_START" = "_OS_INTVEC_CORE3_CODE_START";
    "_OS_INTVEC_CORE3_CODE_ALL_END" = "_OS_INTVEC_CORE3_CODE_END";
    "_OS_INTVEC_CORE3_CODE_ALL_LIMIT" = "_OS_INTVEC_CORE3_CODE_LIMIT";
  }

  group OS_INTVEC_CORE3_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE3_CONST (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE3_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_INTVEC_CORE3_CONST";
      }
    }
    group OS_INTVEC_CORE3_CONST_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE3_CONST_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE3_CONST_START" = "_lc_gb_OS_INTVEC_CORE3_CONST";
    "_OS_INTVEC_CORE3_CONST_END" = ("_lc_gb_OS_INTVEC_CORE3_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE3_CONST_PAD" - 1;
    "_OS_INTVEC_CORE3_CONST_LIMIT" = "_lc_gb_OS_INTVEC_CORE3_CONST_PAD";

    "_OS_INTVEC_CORE3_CONST_ALL_START" = "_OS_INTVEC_CORE3_CONST_START";
    "_OS_INTVEC_CORE3_CONST_ALL_END" = "_OS_INTVEC_CORE3_CONST_END";
    "_OS_INTVEC_CORE3_CONST_ALL_LIMIT" = "_OS_INTVEC_CORE3_CONST_LIMIT";
  }

  group OS_INTVEC_CORE4_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE4_CODE (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE4_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_INTVEC_CORE4_CODE";
      }
    }
    group OS_INTVEC_CORE4_CODE_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE4_CODE_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE4_CODE_START" = "_lc_gb_OS_INTVEC_CORE4_CODE";
    "_OS_INTVEC_CORE4_CODE_END" = ("_lc_gb_OS_INTVEC_CORE4_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE4_CODE_PAD" - 1;
    "_OS_INTVEC_CORE4_CODE_LIMIT" = "_lc_gb_OS_INTVEC_CORE4_CODE_PAD";

    "_OS_INTVEC_CORE4_CODE_ALL_START" = "_OS_INTVEC_CORE4_CODE_START";
    "_OS_INTVEC_CORE4_CODE_ALL_END" = "_OS_INTVEC_CORE4_CODE_END";
    "_OS_INTVEC_CORE4_CODE_ALL_LIMIT" = "_OS_INTVEC_CORE4_CODE_LIMIT";
  }

  group OS_INTVEC_CORE4_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE4_CONST (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE4_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_INTVEC_CORE4_CONST";
      }
    }
    group OS_INTVEC_CORE4_CONST_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE4_CONST_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE4_CONST_START" = "_lc_gb_OS_INTVEC_CORE4_CONST";
    "_OS_INTVEC_CORE4_CONST_END" = ("_lc_gb_OS_INTVEC_CORE4_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE4_CONST_PAD" - 1;
    "_OS_INTVEC_CORE4_CONST_LIMIT" = "_lc_gb_OS_INTVEC_CORE4_CONST_PAD";

    "_OS_INTVEC_CORE4_CONST_ALL_START" = "_OS_INTVEC_CORE4_CONST_START";
    "_OS_INTVEC_CORE4_CONST_ALL_END" = "_OS_INTVEC_CORE4_CONST_END";
    "_OS_INTVEC_CORE4_CONST_ALL_LIMIT" = "_OS_INTVEC_CORE4_CONST_LIMIT";
  }

  group OS_INTVEC_CORE5_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE5_CODE (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE5_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_INTVEC_CORE5_CODE";
      }
    }
    group OS_INTVEC_CORE5_CODE_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE5_CODE_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE5_CODE_START" = "_lc_gb_OS_INTVEC_CORE5_CODE";
    "_OS_INTVEC_CORE5_CODE_END" = ("_lc_gb_OS_INTVEC_CORE5_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE5_CODE_PAD" - 1;
    "_OS_INTVEC_CORE5_CODE_LIMIT" = "_lc_gb_OS_INTVEC_CORE5_CODE_PAD";

    "_OS_INTVEC_CORE5_CODE_ALL_START" = "_OS_INTVEC_CORE5_CODE_START";
    "_OS_INTVEC_CORE5_CODE_ALL_END" = "_OS_INTVEC_CORE5_CODE_END";
    "_OS_INTVEC_CORE5_CODE_ALL_LIMIT" = "_OS_INTVEC_CORE5_CODE_LIMIT";
  }

  group OS_INTVEC_CORE5_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE5_CONST (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE5_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_INTVEC_CORE5_CONST";
      }
    }
    group OS_INTVEC_CORE5_CONST_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE5_CONST_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE5_CONST_START" = "_lc_gb_OS_INTVEC_CORE5_CONST";
    "_OS_INTVEC_CORE5_CONST_END" = ("_lc_gb_OS_INTVEC_CORE5_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE5_CONST_PAD" - 1;
    "_OS_INTVEC_CORE5_CONST_LIMIT" = "_lc_gb_OS_INTVEC_CORE5_CONST_PAD";

    "_OS_INTVEC_CORE5_CONST_ALL_START" = "_OS_INTVEC_CORE5_CONST_START";
    "_OS_INTVEC_CORE5_CONST_ALL_END" = "_OS_INTVEC_CORE5_CONST_END";
    "_OS_INTVEC_CORE5_CONST_ALL_LIMIT" = "_OS_INTVEC_CORE5_CONST_LIMIT";
  }

  group OS_INTVEC_CORE6_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE6_CODE (ordered, contiguous, fill, align = 8192)
    {
      reserved "OS_INTVEC_CORE6_CODE" (size = 0);
    }
    group OS_INTVEC_CORE6_CODE_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE6_CODE_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE6_CODE_START" = "_lc_gb_OS_INTVEC_CORE6_CODE";
    "_OS_INTVEC_CORE6_CODE_END" = ("_lc_gb_OS_INTVEC_CORE6_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE6_CODE_PAD" - 1;
    "_OS_INTVEC_CORE6_CODE_LIMIT" = "_lc_gb_OS_INTVEC_CORE6_CODE_PAD";

    "_OS_INTVEC_CORE6_CODE_ALL_START" = "_OS_INTVEC_CORE6_CODE_START";
    "_OS_INTVEC_CORE6_CODE_ALL_END" = "_OS_INTVEC_CORE6_CODE_END";
    "_OS_INTVEC_CORE6_CODE_ALL_LIMIT" = "_OS_INTVEC_CORE6_CODE_LIMIT";
  }

  group OS_INTVEC_CORE6_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_INTVEC_CORE6_CONST (ordered, contiguous, fill, align = 8192)
    {
      reserved "OS_INTVEC_CORE6_CONST" (size = 0);
    }
    group OS_INTVEC_CORE6_CONST_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE6_CONST_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE6_CONST_START" = "_lc_gb_OS_INTVEC_CORE6_CONST";
    "_OS_INTVEC_CORE6_CONST_END" = ("_lc_gb_OS_INTVEC_CORE6_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE6_CONST_PAD" - 1;
    "_OS_INTVEC_CORE6_CONST_LIMIT" = "_lc_gb_OS_INTVEC_CORE6_CONST_PAD";

    "_OS_INTVEC_CORE6_CONST_ALL_START" = "_OS_INTVEC_CORE6_CONST_START";
    "_OS_INTVEC_CORE6_CONST_ALL_END" = "_OS_INTVEC_CORE6_CONST_END";
    "_OS_INTVEC_CORE6_CONST_ALL_LIMIT" = "_OS_INTVEC_CORE6_CONST_LIMIT";
  }

  group OS_OsApplication_OsCore0_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_OsApplication_OsCore0_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore0_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_OsApplication_OsCore0_VAR_FAST";
          select "[.]zdata.OS_OsApplication_OsCore0_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore0_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_INIT_ROM";
    "_OS_OsApplication_OsCore0_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore0_VAR_FAST_INIT_ROM";

    group OS_OsApplication_OsCore0_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore0_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_OsApplication_OsCore0_VAR";
          select "[.]data.OS_OsApplication_OsCore0_VAR_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore0_VAR_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore0_VAR_INIT_ROM";
    "_OS_OsApplication_OsCore0_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore0_VAR_INIT_ROM";

  }

  group OS_OsApplication_OsCore0_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core0)
  {
    group OS_OsApplication_OsCore0_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore0_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_OsApplication_OsCore0_VAR_FAST";
        select "[.]zdata.OS_OsApplication_OsCore0_VAR_FAST_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore0_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore0_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore0_VAR_FAST_INIT_START" = "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_INIT";
    "_OS_OsApplication_OsCore0_VAR_FAST_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore0_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_INIT_PAD";

    group OS_OsApplication_OsCore0_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore0_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_OsApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_OsApplication_OsCore0_VAR_FAST_NOINIT";
      }
    }
    group OS_OsApplication_OsCore0_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore0_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore0_VAR_FAST_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_NOINIT";
    "_OS_OsApplication_OsCore0_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore0_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_NOINIT_PAD";

    group OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT";
    "_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore0_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_OsApplication_OsCore0_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore0_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_OsApplication_OsCore0_VAR";
        select "[.]data.OS_OsApplication_OsCore0_VAR_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore0_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore0_VAR_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore0_VAR_INIT_START" = "_lc_gb_OS_OsApplication_OsCore0_VAR_INIT";
    "_OS_OsApplication_OsCore0_VAR_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore0_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore0_VAR_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore0_VAR_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore0_VAR_INIT_PAD";

    group OS_OsApplication_OsCore0_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore0_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_OsApplication_OsCore0_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_OsApplication_OsCore0_VAR_NOINIT";
      }
    }
    group OS_OsApplication_OsCore0_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore0_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore0_VAR_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore0_VAR_NOINIT";
    "_OS_OsApplication_OsCore0_VAR_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore0_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore0_VAR_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore0_VAR_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore0_VAR_NOINIT_PAD";

    group OS_OsApplication_OsCore0_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore0_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore0_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore0_VAR_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore0_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore0_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore0_VAR_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore0_VAR_ZERO_INIT";
    "_OS_OsApplication_OsCore0_VAR_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore0_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore0_VAR_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore0_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore0_VAR_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_PAD";

    "_OS_OsApplication_OsCore0_VAR_ALL_START" = "_OS_OsApplication_OsCore0_VAR_FAST_INIT_START";
    "_OS_OsApplication_OsCore0_VAR_ALL_END" = "_OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_END";
    "_OS_OsApplication_OsCore0_VAR_ALL_LIMIT" = "_OS_OsApplication_OsCore0_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_OsApplication_OsCore1_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_OsApplication_OsCore1_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore1_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_OsApplication_OsCore1_VAR_FAST";
          select "[.]zdata.OS_OsApplication_OsCore1_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore1_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_INIT_ROM";
    "_OS_OsApplication_OsCore1_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore1_VAR_FAST_INIT_ROM";

    group OS_OsApplication_OsCore1_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore1_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_OsApplication_OsCore1_VAR";
          select "[.]data.OS_OsApplication_OsCore1_VAR_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore1_VAR_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore1_VAR_INIT_ROM";
    "_OS_OsApplication_OsCore1_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore1_VAR_INIT_ROM";

  }

  group OS_OsApplication_OsCore1_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core1)
  {
    group OS_OsApplication_OsCore1_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore1_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_OsApplication_OsCore1_VAR_FAST";
        select "[.]zdata.OS_OsApplication_OsCore1_VAR_FAST_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore1_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore1_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore1_VAR_FAST_INIT_START" = "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_INIT";
    "_OS_OsApplication_OsCore1_VAR_FAST_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore1_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_INIT_PAD";

    group OS_OsApplication_OsCore1_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore1_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_OsApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_OsApplication_OsCore1_VAR_FAST_NOINIT";
      }
    }
    group OS_OsApplication_OsCore1_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore1_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_NOINIT";
    "_OS_OsApplication_OsCore1_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore1_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_NOINIT_PAD";

    group OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT";
    "_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore1_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_OsApplication_OsCore1_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore1_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_OsApplication_OsCore1_VAR";
        select "[.]data.OS_OsApplication_OsCore1_VAR_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore1_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore1_VAR_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore1_VAR_INIT_START" = "_lc_gb_OS_OsApplication_OsCore1_VAR_INIT";
    "_OS_OsApplication_OsCore1_VAR_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore1_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore1_VAR_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore1_VAR_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore1_VAR_INIT_PAD";

    group OS_OsApplication_OsCore1_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore1_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_OsApplication_OsCore1_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_OsApplication_OsCore1_VAR_NOINIT";
      }
    }
    group OS_OsApplication_OsCore1_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore1_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore1_VAR_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore1_VAR_NOINIT";
    "_OS_OsApplication_OsCore1_VAR_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore1_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore1_VAR_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore1_VAR_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore1_VAR_NOINIT_PAD";

    group OS_OsApplication_OsCore1_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore1_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore1_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore1_VAR_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore1_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore1_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore1_VAR_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore1_VAR_ZERO_INIT";
    "_OS_OsApplication_OsCore1_VAR_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore1_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore1_VAR_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore1_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore1_VAR_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_PAD";

    "_OS_OsApplication_OsCore1_VAR_ALL_START" = "_OS_OsApplication_OsCore1_VAR_FAST_INIT_START";
    "_OS_OsApplication_OsCore1_VAR_ALL_END" = "_OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_END";
    "_OS_OsApplication_OsCore1_VAR_ALL_LIMIT" = "_OS_OsApplication_OsCore1_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_OsApplication_OsCore2_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_OsApplication_OsCore2_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore2_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_OsApplication_OsCore2_VAR_FAST";
          select "[.]zdata.OS_OsApplication_OsCore2_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore2_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_INIT_ROM";
    "_OS_OsApplication_OsCore2_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore2_VAR_FAST_INIT_ROM";

    group OS_OsApplication_OsCore2_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore2_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_OsApplication_OsCore2_VAR";
          select "[.]data.OS_OsApplication_OsCore2_VAR_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore2_VAR_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore2_VAR_INIT_ROM";
    "_OS_OsApplication_OsCore2_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore2_VAR_INIT_ROM";

  }

  group OS_OsApplication_OsCore2_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core2)
  {
    group OS_OsApplication_OsCore2_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore2_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_OsApplication_OsCore2_VAR_FAST";
        select "[.]zdata.OS_OsApplication_OsCore2_VAR_FAST_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore2_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore2_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore2_VAR_FAST_INIT_START" = "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_INIT";
    "_OS_OsApplication_OsCore2_VAR_FAST_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore2_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_INIT_PAD";

    group OS_OsApplication_OsCore2_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore2_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_OsApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_OsApplication_OsCore2_VAR_FAST_NOINIT";
      }
    }
    group OS_OsApplication_OsCore2_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore2_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore2_VAR_FAST_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_NOINIT";
    "_OS_OsApplication_OsCore2_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore2_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_NOINIT_PAD";

    group OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT";
    "_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore2_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_OsApplication_OsCore2_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore2_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_OsApplication_OsCore2_VAR";
        select "[.]data.OS_OsApplication_OsCore2_VAR_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore2_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore2_VAR_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore2_VAR_INIT_START" = "_lc_gb_OS_OsApplication_OsCore2_VAR_INIT";
    "_OS_OsApplication_OsCore2_VAR_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore2_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore2_VAR_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore2_VAR_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore2_VAR_INIT_PAD";

    group OS_OsApplication_OsCore2_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore2_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_OsApplication_OsCore2_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_OsApplication_OsCore2_VAR_NOINIT";
      }
    }
    group OS_OsApplication_OsCore2_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore2_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore2_VAR_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore2_VAR_NOINIT";
    "_OS_OsApplication_OsCore2_VAR_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore2_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore2_VAR_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore2_VAR_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore2_VAR_NOINIT_PAD";

    group OS_OsApplication_OsCore2_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore2_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore2_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore2_VAR_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore2_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore2_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore2_VAR_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore2_VAR_ZERO_INIT";
    "_OS_OsApplication_OsCore2_VAR_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore2_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore2_VAR_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore2_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore2_VAR_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_PAD";

    "_OS_OsApplication_OsCore2_VAR_ALL_START" = "_OS_OsApplication_OsCore2_VAR_FAST_INIT_START";
    "_OS_OsApplication_OsCore2_VAR_ALL_END" = "_OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_END";
    "_OS_OsApplication_OsCore2_VAR_ALL_LIMIT" = "_OS_OsApplication_OsCore2_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_OsApplication_OsCore3_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_OsApplication_OsCore3_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore3_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_OsApplication_OsCore3_VAR_FAST";
          select "[.]zdata.OS_OsApplication_OsCore3_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore3_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_INIT_ROM";
    "_OS_OsApplication_OsCore3_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore3_VAR_FAST_INIT_ROM";

    group OS_OsApplication_OsCore3_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore3_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_OsApplication_OsCore3_VAR";
          select "[.]data.OS_OsApplication_OsCore3_VAR_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore3_VAR_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore3_VAR_INIT_ROM";
    "_OS_OsApplication_OsCore3_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore3_VAR_INIT_ROM";

  }

  group OS_OsApplication_OsCore3_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core3)
  {
    group OS_OsApplication_OsCore3_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore3_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_OsApplication_OsCore3_VAR_FAST";
        select "[.]zdata.OS_OsApplication_OsCore3_VAR_FAST_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore3_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore3_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore3_VAR_FAST_INIT_START" = "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_INIT";
    "_OS_OsApplication_OsCore3_VAR_FAST_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore3_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_INIT_PAD";

    group OS_OsApplication_OsCore3_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore3_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_OsApplication_OsCore3_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_OsApplication_OsCore3_VAR_FAST_NOINIT";
      }
    }
    group OS_OsApplication_OsCore3_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore3_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore3_VAR_FAST_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_NOINIT";
    "_OS_OsApplication_OsCore3_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore3_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_NOINIT_PAD";

    group OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore3_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT";
    "_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore3_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore3_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_OsApplication_OsCore3_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore3_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_OsApplication_OsCore3_VAR";
        select "[.]data.OS_OsApplication_OsCore3_VAR_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore3_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore3_VAR_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore3_VAR_INIT_START" = "_lc_gb_OS_OsApplication_OsCore3_VAR_INIT";
    "_OS_OsApplication_OsCore3_VAR_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore3_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore3_VAR_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore3_VAR_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore3_VAR_INIT_PAD";

    group OS_OsApplication_OsCore3_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore3_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_OsApplication_OsCore3_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_OsApplication_OsCore3_VAR_NOINIT";
      }
    }
    group OS_OsApplication_OsCore3_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore3_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore3_VAR_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore3_VAR_NOINIT";
    "_OS_OsApplication_OsCore3_VAR_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore3_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore3_VAR_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore3_VAR_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore3_VAR_NOINIT_PAD";

    group OS_OsApplication_OsCore3_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore3_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore3_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore3_VAR_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore3_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore3_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore3_VAR_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore3_VAR_ZERO_INIT";
    "_OS_OsApplication_OsCore3_VAR_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore3_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore3_VAR_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore3_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore3_VAR_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore3_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_PAD";

    "_OS_OsApplication_OsCore3_VAR_ALL_START" = "_OS_OsApplication_OsCore3_VAR_FAST_INIT_START";
    "_OS_OsApplication_OsCore3_VAR_ALL_END" = "_OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_END";
    "_OS_OsApplication_OsCore3_VAR_ALL_LIMIT" = "_OS_OsApplication_OsCore3_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_OsApplication_OsCore4_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_OsApplication_OsCore4_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore4_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_OsApplication_OsCore4_VAR_FAST";
          select "[.]zdata.OS_OsApplication_OsCore4_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore4_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_INIT_ROM";
    "_OS_OsApplication_OsCore4_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore4_VAR_FAST_INIT_ROM";

    group OS_OsApplication_OsCore4_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore4_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_OsApplication_OsCore4_VAR";
          select "[.]data.OS_OsApplication_OsCore4_VAR_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore4_VAR_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore4_VAR_INIT_ROM";
    "_OS_OsApplication_OsCore4_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore4_VAR_INIT_ROM";

  }

  group OS_OsApplication_OsCore4_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core4)
  {
    group OS_OsApplication_OsCore4_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore4_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_OsApplication_OsCore4_VAR_FAST";
        select "[.]zdata.OS_OsApplication_OsCore4_VAR_FAST_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore4_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore4_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore4_VAR_FAST_INIT_START" = "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_INIT";
    "_OS_OsApplication_OsCore4_VAR_FAST_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore4_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_INIT_PAD";

    group OS_OsApplication_OsCore4_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore4_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_OsApplication_OsCore4_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_OsApplication_OsCore4_VAR_FAST_NOINIT";
      }
    }
    group OS_OsApplication_OsCore4_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore4_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore4_VAR_FAST_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_NOINIT";
    "_OS_OsApplication_OsCore4_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore4_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_NOINIT_PAD";

    group OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore4_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT";
    "_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore4_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore4_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_OsApplication_OsCore4_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore4_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_OsApplication_OsCore4_VAR";
        select "[.]data.OS_OsApplication_OsCore4_VAR_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore4_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore4_VAR_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore4_VAR_INIT_START" = "_lc_gb_OS_OsApplication_OsCore4_VAR_INIT";
    "_OS_OsApplication_OsCore4_VAR_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore4_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore4_VAR_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore4_VAR_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore4_VAR_INIT_PAD";

    group OS_OsApplication_OsCore4_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore4_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_OsApplication_OsCore4_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_OsApplication_OsCore4_VAR_NOINIT";
      }
    }
    group OS_OsApplication_OsCore4_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore4_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore4_VAR_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore4_VAR_NOINIT";
    "_OS_OsApplication_OsCore4_VAR_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore4_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore4_VAR_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore4_VAR_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore4_VAR_NOINIT_PAD";

    group OS_OsApplication_OsCore4_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore4_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore4_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore4_VAR_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore4_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore4_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore4_VAR_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore4_VAR_ZERO_INIT";
    "_OS_OsApplication_OsCore4_VAR_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore4_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore4_VAR_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore4_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore4_VAR_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore4_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_PAD";

    "_OS_OsApplication_OsCore4_VAR_ALL_START" = "_OS_OsApplication_OsCore4_VAR_FAST_INIT_START";
    "_OS_OsApplication_OsCore4_VAR_ALL_END" = "_OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_END";
    "_OS_OsApplication_OsCore4_VAR_ALL_LIMIT" = "_OS_OsApplication_OsCore4_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_OsApplication_OsCore5_VAR_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_OsApplication_OsCore5_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore5_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_OsApplication_OsCore5_VAR_FAST";
          select "[.]zdata.OS_OsApplication_OsCore5_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore5_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_INIT_ROM";
    "_OS_OsApplication_OsCore5_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore5_VAR_FAST_INIT_ROM";

    group OS_OsApplication_OsCore5_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore5_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_OsApplication_OsCore5_VAR";
          select "[.]data.OS_OsApplication_OsCore5_VAR_NOCACHE";
        }
      }
    }
    "_OS_OsApplication_OsCore5_VAR_INIT_ROM_START" = "_lc_gb_OS_OsApplication_OsCore5_VAR_INIT_ROM";
    "_OS_OsApplication_OsCore5_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_OsApplication_OsCore5_VAR_INIT_ROM";

  }

  group OS_OsApplication_OsCore5_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core5)
  {
    group OS_OsApplication_OsCore5_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore5_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_OsApplication_OsCore5_VAR_FAST";
        select "[.]zdata.OS_OsApplication_OsCore5_VAR_FAST_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore5_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore5_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore5_VAR_FAST_INIT_START" = "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_INIT";
    "_OS_OsApplication_OsCore5_VAR_FAST_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore5_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_INIT_PAD";

    group OS_OsApplication_OsCore5_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore5_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_OsApplication_OsCore5_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_OsApplication_OsCore5_VAR_FAST_NOINIT";
      }
    }
    group OS_OsApplication_OsCore5_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore5_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore5_VAR_FAST_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_NOINIT";
    "_OS_OsApplication_OsCore5_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore5_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_NOINIT_PAD";

    group OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore5_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT";
    "_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore5_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore5_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_OsApplication_OsCore5_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore5_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_OsApplication_OsCore5_VAR";
        select "[.]data.OS_OsApplication_OsCore5_VAR_NOCACHE";
      }
    }
    group OS_OsApplication_OsCore5_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore5_VAR_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore5_VAR_INIT_START" = "_lc_gb_OS_OsApplication_OsCore5_VAR_INIT";
    "_OS_OsApplication_OsCore5_VAR_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore5_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore5_VAR_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore5_VAR_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore5_VAR_INIT_PAD";

    group OS_OsApplication_OsCore5_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore5_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_OsApplication_OsCore5_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_OsApplication_OsCore5_VAR_NOINIT";
      }
    }
    group OS_OsApplication_OsCore5_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_OsApplication_OsCore5_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore5_VAR_NOINIT_START" = "_lc_gb_OS_OsApplication_OsCore5_VAR_NOINIT";
    "_OS_OsApplication_OsCore5_VAR_NOINIT_END" = ("_lc_gb_OS_OsApplication_OsCore5_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore5_VAR_NOINIT_PAD" - 1;
    "_OS_OsApplication_OsCore5_VAR_NOINIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore5_VAR_NOINIT_PAD";

    group OS_OsApplication_OsCore5_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore5_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore5_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_OsApplication_OsCore5_VAR_ZERO_INIT";
      }
    }
    group OS_OsApplication_OsCore5_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore5_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore5_VAR_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_OsCore5_VAR_ZERO_INIT";
    "_OS_OsApplication_OsCore5_VAR_ZERO_INIT_END" = ("_lc_gb_OS_OsApplication_OsCore5_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore5_VAR_ZERO_INIT_PAD" - 1;
    "_OS_OsApplication_OsCore5_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_OsApplication_OsCore5_VAR_ZERO_INIT_PAD";

    group OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_OsApplication_OsCore5_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss";
      }
    }
    group OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss";
    "_OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_PAD";

    "_OS_OsApplication_OsCore5_VAR_ALL_START" = "_OS_OsApplication_OsCore5_VAR_FAST_INIT_START";
    "_OS_OsApplication_OsCore5_VAR_ALL_END" = "_OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_END";
    "_OS_OsApplication_OsCore5_VAR_ALL_LIMIT" = "_OS_OsApplication_OsCore5_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_STACKS_CORE0_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core0)
  {
    group OS_STACKS_CORE0_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_STACKS_CORE0_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_STACK_OSCORE0_ERROR_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_INIT_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_KERNEL_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_SHUTDOWN_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_STARTUP_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_TASK_PRIO20_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_TASK_PRIO40_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_TASK_PRIO48_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_TASK_PRIO50_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_TASK_PRIO55_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSTASK_ASW_OSCORE0_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSTASK_BSW_10MS_CORE0_VAR_NOINIT";
      }
    }
    group OS_STACKS_CORE0_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_STACKS_CORE0_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_STACKS_CORE0_VAR_NOINIT_START" = "_lc_gb_OS_STACKS_CORE0_VAR_NOINIT";
    "_OS_STACKS_CORE0_VAR_NOINIT_END" = ("_lc_gb_OS_STACKS_CORE0_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_STACKS_CORE0_VAR_NOINIT_PAD" - 1;
    "_OS_STACKS_CORE0_VAR_NOINIT_LIMIT" = "_lc_gb_OS_STACKS_CORE0_VAR_NOINIT_PAD";

    "_OS_STACKS_CORE0_VAR_ALL_START" = "_OS_STACKS_CORE0_VAR_NOINIT_START";
    "_OS_STACKS_CORE0_VAR_ALL_END" = "_OS_STACKS_CORE0_VAR_NOINIT_END";
    "_OS_STACKS_CORE0_VAR_ALL_LIMIT" = "_OS_STACKS_CORE0_VAR_NOINIT_LIMIT";
  }

  group OS_STACKS_CORE1_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core1)
  {
    group OS_STACKS_CORE1_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_STACKS_CORE1_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_STACK_OSCORE1_ERROR_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_INIT_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_ISR_CORE_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_KERNEL_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_SHUTDOWN_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_STARTUP_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_TASK_PRIO14_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_TASK_PRIO34_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_TASK_PRIO41_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_TASK_PRIO48_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_TASK_PRIO49_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT";
      }
    }
    group OS_STACKS_CORE1_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_STACKS_CORE1_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_STACKS_CORE1_VAR_NOINIT_START" = "_lc_gb_OS_STACKS_CORE1_VAR_NOINIT";
    "_OS_STACKS_CORE1_VAR_NOINIT_END" = ("_lc_gb_OS_STACKS_CORE1_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_STACKS_CORE1_VAR_NOINIT_PAD" - 1;
    "_OS_STACKS_CORE1_VAR_NOINIT_LIMIT" = "_lc_gb_OS_STACKS_CORE1_VAR_NOINIT_PAD";

    "_OS_STACKS_CORE1_VAR_ALL_START" = "_OS_STACKS_CORE1_VAR_NOINIT_START";
    "_OS_STACKS_CORE1_VAR_ALL_END" = "_OS_STACKS_CORE1_VAR_NOINIT_END";
    "_OS_STACKS_CORE1_VAR_ALL_LIMIT" = "_OS_STACKS_CORE1_VAR_NOINIT_LIMIT";
  }

  group OS_STACKS_CORE2_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core2)
  {
    group OS_STACKS_CORE2_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_STACKS_CORE2_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_STACK_OSCORE2_ERROR_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_INIT_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_ISR_CORE_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_KERNEL_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_STARTUP_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT";
      }
    }
    group OS_STACKS_CORE2_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_STACKS_CORE2_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_STACKS_CORE2_VAR_NOINIT_START" = "_lc_gb_OS_STACKS_CORE2_VAR_NOINIT";
    "_OS_STACKS_CORE2_VAR_NOINIT_END" = ("_lc_gb_OS_STACKS_CORE2_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_STACKS_CORE2_VAR_NOINIT_PAD" - 1;
    "_OS_STACKS_CORE2_VAR_NOINIT_LIMIT" = "_lc_gb_OS_STACKS_CORE2_VAR_NOINIT_PAD";

    "_OS_STACKS_CORE2_VAR_ALL_START" = "_OS_STACKS_CORE2_VAR_NOINIT_START";
    "_OS_STACKS_CORE2_VAR_ALL_END" = "_OS_STACKS_CORE2_VAR_NOINIT_END";
    "_OS_STACKS_CORE2_VAR_ALL_LIMIT" = "_OS_STACKS_CORE2_VAR_NOINIT_LIMIT";
  }

  group OS_STACKS_CORE3_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core3)
  {
    group OS_STACKS_CORE3_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_STACKS_CORE3_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_STACK_OSCORE3_ERROR_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_INIT_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_ISR_CORE_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_KERNEL_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_SHUTDOWN_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_STARTUP_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_TASK_PRIO12_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_TASK_PRIO32_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_TASK_PRIO4294967295_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_TASK_PRIO48_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_TASK_PRIO49_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE3_TASK_PRIO52_VAR_NOINIT";
      }
    }
    group OS_STACKS_CORE3_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_STACKS_CORE3_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_STACKS_CORE3_VAR_NOINIT_START" = "_lc_gb_OS_STACKS_CORE3_VAR_NOINIT";
    "_OS_STACKS_CORE3_VAR_NOINIT_END" = ("_lc_gb_OS_STACKS_CORE3_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_STACKS_CORE3_VAR_NOINIT_PAD" - 1;
    "_OS_STACKS_CORE3_VAR_NOINIT_LIMIT" = "_lc_gb_OS_STACKS_CORE3_VAR_NOINIT_PAD";

    "_OS_STACKS_CORE3_VAR_ALL_START" = "_OS_STACKS_CORE3_VAR_NOINIT_START";
    "_OS_STACKS_CORE3_VAR_ALL_END" = "_OS_STACKS_CORE3_VAR_NOINIT_END";
    "_OS_STACKS_CORE3_VAR_ALL_LIMIT" = "_OS_STACKS_CORE3_VAR_NOINIT_LIMIT";
  }

  group OS_STACKS_CORE4_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core4)
  {
    group OS_STACKS_CORE4_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_STACKS_CORE4_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_STACK_OSCORE4_ERROR_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_INIT_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_ISR_CORE_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_KERNEL_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_SHUTDOWN_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_STARTUP_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_TASK_PRIO11_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_TASK_PRIO31_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_TASK_PRIO4294967295_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_TASK_PRIO48_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_TASK_PRIO49_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE4_TASK_PRIO51_VAR_NOINIT";
      }
    }
    group OS_STACKS_CORE4_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_STACKS_CORE4_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_STACKS_CORE4_VAR_NOINIT_START" = "_lc_gb_OS_STACKS_CORE4_VAR_NOINIT";
    "_OS_STACKS_CORE4_VAR_NOINIT_END" = ("_lc_gb_OS_STACKS_CORE4_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_STACKS_CORE4_VAR_NOINIT_PAD" - 1;
    "_OS_STACKS_CORE4_VAR_NOINIT_LIMIT" = "_lc_gb_OS_STACKS_CORE4_VAR_NOINIT_PAD";

    "_OS_STACKS_CORE4_VAR_ALL_START" = "_OS_STACKS_CORE4_VAR_NOINIT_START";
    "_OS_STACKS_CORE4_VAR_ALL_END" = "_OS_STACKS_CORE4_VAR_NOINIT_END";
    "_OS_STACKS_CORE4_VAR_ALL_LIMIT" = "_OS_STACKS_CORE4_VAR_NOINIT_LIMIT";
  }

  group OS_STACKS_CORE5_VAR_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core5)
  {
    group OS_STACKS_CORE5_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_STACKS_CORE5_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_STACK_OSCORE5_ERROR_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_INIT_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_ISR_CORE_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_KERNEL_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_SHUTDOWN_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_STARTUP_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_TASK_PRIO10_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_TASK_PRIO30_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_TASK_PRIO4294967295_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_TASK_PRIO48_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_TASK_PRIO49_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE5_TASK_PRIO50_VAR_NOINIT";
      }
    }
    group OS_STACKS_CORE5_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_STACKS_CORE5_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_STACKS_CORE5_VAR_NOINIT_START" = "_lc_gb_OS_STACKS_CORE5_VAR_NOINIT";
    "_OS_STACKS_CORE5_VAR_NOINIT_END" = ("_lc_gb_OS_STACKS_CORE5_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_STACKS_CORE5_VAR_NOINIT_PAD" - 1;
    "_OS_STACKS_CORE5_VAR_NOINIT_LIMIT" = "_lc_gb_OS_STACKS_CORE5_VAR_NOINIT_PAD";

    "_OS_STACKS_CORE5_VAR_ALL_START" = "_OS_STACKS_CORE5_VAR_NOINIT_START";
    "_OS_STACKS_CORE5_VAR_ALL_END" = "_OS_STACKS_CORE5_VAR_NOINIT_END";
    "_OS_STACKS_CORE5_VAR_ALL_LIMIT" = "_OS_STACKS_CORE5_VAR_NOINIT_LIMIT";
  }

  group OS_USER_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_USER_CODE (ordered, contiguous, fill)
    {
      section "OS_USER_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_Default_Init_Task_CODE";
        select "[.]text.OS_Default_Init_Task_Core1_CODE";
        select "[.]text.OS_Default_Init_Task_Core1_Trusted_CODE";
        select "[.]text.OS_Default_Init_Task_Core2_CODE";
        select "[.]text.OS_Default_Init_Task_Core2_Trusted_CODE";
        select "[.]text.OS_Default_Init_Task_Core3_CODE";
        select "[.]text.OS_Default_Init_Task_Core3_Trusted_CODE";
        select "[.]text.OS_Default_Init_Task_Core4_CODE";
        select "[.]text.OS_Default_Init_Task_Core4_Trusted_CODE";
        select "[.]text.OS_Default_Init_Task_Core6_CODE";
        select "[.]text.OS_Default_Init_Task_Core6_Trusted_CODE";
        select "[.]text.OS_Default_Init_Task_Trusted_CODE";
        select "[.]text.OS_ERRORHOOK_CODE";
        select "[.]text.OS_EthIsr_EthCtrlConfig_EthInterruptServiceRoutine_CODE";
        select "[.]text.OS_OsTask_Asw_OsCore0_CODE";
        select "[.]text.OS_OsTask_Asw_OsCore1_CODE";
        select "[.]text.OS_OsTask_Asw_OsCore2_CODE";
        select "[.]text.OS_OsTask_Asw_OsCore3_CODE";
        select "[.]text.OS_OsTask_Asw_OsCore4_CODE";
        select "[.]text.OS_OsTask_Asw_OsCore5_CODE";
        select "[.]text.OS_OsTask_Bsw_10ms_Core0_CODE";
        select "[.]text.OS_OsTask_Bsw_1ms_Core0_CODE";
        select "[.]text.OS_OsTask_Bsw_20ms_Core0_CODE";
        select "[.]text.OS_OsTask_Bsw_5ms_Core0_CODE";
        select "[.]text.OS_OsTask_Bsw_OsCore1_CODE";
        select "[.]text.OS_OsTask_Bsw_OsCore2_CODE";
        select "[.]text.OS_OsTask_Bsw_OsCore3_CODE";
        select "[.]text.OS_OsTask_Bsw_OsCore4_CODE";
        select "[.]text.OS_OsTask_Bsw_OsCore5_CODE";
        select "[.]text.OS_OsTask_Init_OsCore0_CODE";
        select "[.]text.OS_OsTask_Init_OsCore1_CODE";
        select "[.]text.OS_OsTask_Init_OsCore2_CODE";
        select "[.]text.OS_OsTask_Init_OsCore3_CODE";
        select "[.]text.OS_OsTask_Init_OsCore4_CODE";
        select "[.]text.OS_OsTask_Init_OsCore5_CODE";
        select "[.]text.OS_OsTask_lock_2ms_CODE";
        select "[.]text.OS_OsTask_window_2ms_CODE";
        select "[.]text.OS_POSTTASKHOOK_CODE";
        select "[.]text.OS_PRETASKHOOK_CODE";
        select "[.]text.OS_SHUTDOWNHOOK_CODE";
        select "[.]text.OS_STARTUPHOOK_CODE";
      }
    }
    group OS_USER_CODE_PAD (align = 1)
    {
      reserved "OS_USER_CODE_PAD" (size = 16);
    }
    "_OS_USER_CODE_START" = "_lc_gb_OS_USER_CODE";
    "_OS_USER_CODE_END" = ("_lc_gb_OS_USER_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_USER_CODE_PAD" - 1;
    "_OS_USER_CODE_LIMIT" = "_lc_gb_OS_USER_CODE_PAD";

    "_OS_USER_CODE_ALL_START" = "_OS_USER_CODE_START";
    "_OS_USER_CODE_ALL_END" = "_OS_USER_CODE_END";
    "_OS_USER_CODE_ALL_LIMIT" = "_OS_USER_CODE_LIMIT";
  }

  group OS_USER_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_USER_CONST (ordered, contiguous, fill)
    {
      section "OS_USER_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_OsApplication_OsCore0_CONST";
        select "[.]zrodata.OS_OsApplication_OsCore0_CONST_FAST";
        select "[.]rodata.OS_OsApplication_OsCore1_CONST";
        select "[.]zrodata.OS_OsApplication_OsCore1_CONST_FAST";
        select "[.]rodata.OS_OsApplication_OsCore2_CONST";
        select "[.]zrodata.OS_OsApplication_OsCore2_CONST_FAST";
        select "[.]rodata.OS_OsApplication_OsCore3_CONST";
        select "[.]zrodata.OS_OsApplication_OsCore3_CONST_FAST";
        select "[.]rodata.OS_OsApplication_OsCore4_CONST";
        select "[.]zrodata.OS_OsApplication_OsCore4_CONST_FAST";
        select "[.]rodata.OS_OsApplication_OsCore5_CONST";
        select "[.]zrodata.OS_OsApplication_OsCore5_CONST_FAST";
      }
    }
    group OS_USER_CONST_PAD (align = 1)
    {
      reserved "OS_USER_CONST_PAD" (size = 16);
    }
    "_OS_USER_CONST_START" = "_lc_gb_OS_USER_CONST";
    "_OS_USER_CONST_END" = ("_lc_gb_OS_USER_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_USER_CONST_PAD" - 1;
    "_OS_USER_CONST_LIMIT" = "_lc_gb_OS_USER_CONST_PAD";

    "_OS_USER_CONST_ALL_START" = "_OS_USER_CONST_START";
    "_OS_USER_CONST_ALL_END" = "_OS_USER_CONST_END";
    "_OS_USER_CONST_ALL_LIMIT" = "_OS_USER_CONST_LIMIT";
  }

  group Reg_Data_DO_NOT_DELETE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core0)
  {
    group Reg_A0Data_DO_NOT_DELETE (ordered, contiguous, fill, align = 4)
    {
      section "Reg_A0Data_DO_NOT_DELETE_SEC" (blocksize = 2, attributes = rw)
      {
        select ".data_a0.sdata|.data_a0.sdata.*|.bss_a0.sbss|.bss_a0.sbss.*";
      }
    }
    "_Reg_A0Data_DO_NOT_DELETE_START" = "_lc_gb_Reg_A0Data_DO_NOT_DELETE";
    "_Reg_A0Data_DO_NOT_DELETE_END" = ("_lc_ge_Reg_A0Data_DO_NOT_DELETE" == 0) ? 0 : "_lc_ge_Reg_A0Data_DO_NOT_DELETE" - 1;
    "_Reg_A0Data_DO_NOT_DELETE_LIMIT" = "_lc_ge_Reg_A0Data_DO_NOT_DELETE";

    group Reg_A1Data_DO_NOT_DELETE (ordered, contiguous, fill, align = 4)
    {
      section "Reg_A1Data_DO_NOT_DELETE_SEC" (blocksize = 2, attributes = rw)
      {
        select ".rodata_a1.srodata|.rodata_a1.srodata.*|.ldata|.ldata.*";
      }
    }
    "_Reg_A1Data_DO_NOT_DELETE_START" = "_lc_gb_Reg_A1Data_DO_NOT_DELETE";
    "_Reg_A1Data_DO_NOT_DELETE_END" = ("_lc_ge_Reg_A1Data_DO_NOT_DELETE" == 0) ? 0 : "_lc_ge_Reg_A1Data_DO_NOT_DELETE" - 1;
    "_Reg_A1Data_DO_NOT_DELETE_LIMIT" = "_lc_ge_Reg_A1Data_DO_NOT_DELETE";

    group Reg_A8Data_DO_NOT_DELETE (ordered, contiguous, fill, align = 4)
    {
      section "Reg_A8Data_DO_NOT_DELETE_SEC" (blocksize = 2, attributes = rw)
      {
        select ".rodata_a8.a8srodata|.rodata_a8.a8srodata.*";
      }
    }
    "_Reg_A8Data_DO_NOT_DELETE_START" = "_lc_gb_Reg_A8Data_DO_NOT_DELETE";
    "_Reg_A8Data_DO_NOT_DELETE_END" = ("_lc_ge_Reg_A8Data_DO_NOT_DELETE" == 0) ? 0 : "_lc_ge_Reg_A8Data_DO_NOT_DELETE" - 1;
    "_Reg_A8Data_DO_NOT_DELETE_LIMIT" = "_lc_ge_Reg_A8Data_DO_NOT_DELETE";

    group Reg_A9Data_DO_NOT_DELETE (ordered, contiguous, fill, align = 4)
    {
      section "Reg_A9Data_DO_NOT_DELETE_SEC" (blocksize = 2, attributes = rw)
      {
        select ".data_a9.a9sdata|.data_a9.a9sdata.*|.bss_a9.a9sbss|.bss_a9.a9sbss.*";
      }
    }
    "_Reg_A9Data_DO_NOT_DELETE_START" = "_lc_gb_Reg_A9Data_DO_NOT_DELETE";
    "_Reg_A9Data_DO_NOT_DELETE_END" = ("_lc_ge_Reg_A9Data_DO_NOT_DELETE" == 0) ? 0 : "_lc_ge_Reg_A9Data_DO_NOT_DELETE" - 1;
    "_Reg_A9Data_DO_NOT_DELETE_LIMIT" = "_lc_ge_Reg_A9Data_DO_NOT_DELETE";

    "_Reg_Data_DO_NOT_DELETE_ALL_START" = "_Reg_A0Data_DO_NOT_DELETE_START";
    "_Reg_Data_DO_NOT_DELETE_ALL_END" = "_Reg_A9Data_DO_NOT_DELETE_END";
    "_Reg_Data_DO_NOT_DELETE_ALL_LIMIT" = "_Reg_A9Data_DO_NOT_DELETE_LIMIT";
  }

  "_SMALL_DATA_TC1" = "_Reg_A0Data_DO_NOT_DELETE_LIMIT"-"_Reg_A0Data_DO_NOT_DELETE_START";
  "_SMALL_DATA_TC2" = "_SMALL_DATA_TC1";
  "_SMALL_DATA_TC3" = "_SMALL_DATA_TC1";
  "_SMALL_DATA_TC4" = "_SMALL_DATA_TC1";
  "_SMALL_DATA_TC5" = "_SMALL_DATA_TC1";
  "_LITERAL_DATA_TC1" = "_Reg_A1Data_DO_NOT_DELETE_LIMIT"-"_Reg_A1Data_DO_NOT_DELETE_START";
  "_LITERAL_DATA_TC2" = "_LITERAL_DATA_TC1";
  "_LITERAL_DATA_TC3" = "_LITERAL_DATA_TC1";
  "_LITERAL_DATA_TC4" = "_LITERAL_DATA_TC1";
  "_LITERAL_DATA_TC5" = "_LITERAL_DATA_TC1";
  "_A8_DATA_TC1" = "_Reg_A8Data_DO_NOT_DELETE_LIMIT"-"_Reg_A8Data_DO_NOT_DELETE_START";
  "_A8_DATA_TC2" = "_A8_DATA_TC1";
  "_A8_DATA_TC3" = "_A8_DATA_TC1";
  "_A8_DATA_TC4" = "_A8_DATA_TC1";
  "_A8_DATA_TC5" = "_A8_DATA_TC1";
  "_A9_DATA_TC1" = "_Reg_A9Data_DO_NOT_DELETE_LIMIT"-"_Reg_A9Data_DO_NOT_DELETE_START";
  "_A9_DATA_TC2" = "_A9_DATA_TC1";
  "_A9_DATA_TC3" = "_A9_DATA_TC1";
  "_A9_DATA_TC4" = "_A9_DATA_TC1";
  "_A9_DATA_TC5" = "_A9_DATA_TC1";
  "_lc_u_int_tab_tc1" = 0;
  "_lc_u_int_tab_tc2" = 0;
  "_lc_u_int_tab_tc3" = 0;
  "_lc_u_int_tab_tc4" = 0;
  "_lc_u_int_tab_tc5" = 0;
  "_lc_u_trap_tab_tc1" = 0;
  "_lc_u_trap_tab_tc2" = 0;
  "_lc_u_trap_tab_tc3" = 0;
  "_lc_u_trap_tab_tc4" = 0;
  "_lc_u_trap_tab_tc5" = 0;
  "_lc_ub_csa_tc1" = 0;
  "_lc_ub_csa_tc2" = 0;
  "_lc_ub_csa_tc3" = 0;
  "_lc_ub_csa_tc4" = 0;
  "_lc_ub_csa_tc5" = 0;
  "_lc_ub_table_tc1" = 0;
  "_lc_ub_table_tc2" = 0;
  "_lc_ub_table_tc3" = 0;
  "_lc_ub_table_tc4" = 0;
  "_lc_ub_table_tc5" = 0;
  "_lc_ub_ustack_tc1" = 0;
  "_lc_ub_ustack_tc2" = 0;
  "_lc_ub_ustack_tc3" = 0;
  "_lc_ub_ustack_tc4" = 0;
  "_lc_ub_ustack_tc5" = 0;
  "_lc_ue_csa_tc1" = 0;
  "_lc_ue_csa_tc2" = 0;
  "_lc_ue_csa_tc3" = 0;
  "_lc_ue_csa_tc4" = 0;
  "_lc_ue_csa_tc5" = 0;
  "_lc_ue_istack_tc1" = 0;
  "_lc_ue_istack_tc2" = 0;
  "_lc_ue_istack_tc3" = 0;
  "_lc_ue_istack_tc4" = 0;
  "_lc_ue_istack_tc5" = 0;
  "_lc_ue_ustack_tc1" = 0;
  "_lc_ue_ustack_tc2" = 0;
  "_lc_ue_ustack_tc3" = 0;
  "_lc_ue_ustack_tc4" = 0;
  "_lc_ue_ustack_tc5" = 0;

  group STACK_C0_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core0)
  {
    group STACK_C0 (ordered, contiguous, fill, align = 4)
    {
      reserved "STACK_C0" (size = 1024);
    }
    group STACK_C0_PAD (align = 4)
    {
      reserved "STACK_C0_PAD" (size = 0);
    }
    "_STACK_C0_START" = "_lc_gb_STACK_C0";
    "_STACK_C0_END" = ("_lc_ge_STACK_C0" == 0) ? 0 : "_lc_ge_STACK_C0" - 1;
    "_STACK_C0_LIMIT" = "_lc_ge_STACK_C0";

    "_STACK_C0_ALL_START" = "_STACK_C0_START";
    "_STACK_C0_ALL_END" = "_STACK_C0_END";
    "_STACK_C0_ALL_LIMIT" = "_STACK_C0_LIMIT";
  }

  group STACK_C1_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core1)
  {
    group STACK_C1 (ordered, contiguous, fill, align = 4)
    {
      reserved "STACK_C1" (size = 1024);
    }
    group STACK_C1_PAD (align = 4)
    {
      reserved "STACK_C1_PAD" (size = 0);
    }
    "_STACK_C1_START" = "_lc_gb_STACK_C1";
    "_STACK_C1_END" = ("_lc_ge_STACK_C1" == 0) ? 0 : "_lc_ge_STACK_C1" - 1;
    "_STACK_C1_LIMIT" = "_lc_ge_STACK_C1";

    "_STACK_C1_ALL_START" = "_STACK_C1_START";
    "_STACK_C1_ALL_END" = "_STACK_C1_END";
    "_STACK_C1_ALL_LIMIT" = "_STACK_C1_LIMIT";
  }

  group STACK_C2_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core2)
  {
    group STACK_C2 (ordered, contiguous, fill, align = 4)
    {
      reserved "STACK_C2" (size = 1024);
    }
    group STACK_C2_PAD (align = 4)
    {
      reserved "STACK_C2_PAD" (size = 0);
    }
    "_STACK_C2_START" = "_lc_gb_STACK_C2";
    "_STACK_C2_END" = ("_lc_ge_STACK_C2" == 0) ? 0 : "_lc_ge_STACK_C2" - 1;
    "_STACK_C2_LIMIT" = "_lc_ge_STACK_C2";

    "_STACK_C2_ALL_START" = "_STACK_C2_START";
    "_STACK_C2_ALL_END" = "_STACK_C2_END";
    "_STACK_C2_ALL_LIMIT" = "_STACK_C2_LIMIT";
  }

  group STACK_C3_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core3)
  {
    group STACK_C3 (ordered, contiguous, fill, align = 4)
    {
      reserved "STACK_C3" (size = 1024);
    }
    group STACK_C3_PAD (align = 4)
    {
      reserved "STACK_C3_PAD" (size = 0);
    }
    "_STACK_C3_START" = "_lc_gb_STACK_C3";
    "_STACK_C3_END" = ("_lc_ge_STACK_C3" == 0) ? 0 : "_lc_ge_STACK_C3" - 1;
    "_STACK_C3_LIMIT" = "_lc_ge_STACK_C3";

    "_STACK_C3_ALL_START" = "_STACK_C3_START";
    "_STACK_C3_ALL_END" = "_STACK_C3_END";
    "_STACK_C3_ALL_LIMIT" = "_STACK_C3_LIMIT";
  }

  group STACK_C4_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core4)
  {
    group STACK_C4 (ordered, contiguous, fill, align = 4)
    {
      reserved "STACK_C4" (size = 1024);
    }
    group STACK_C4_PAD (align = 4)
    {
      reserved "STACK_C4_PAD" (size = 0);
    }
    "_STACK_C4_START" = "_lc_gb_STACK_C4";
    "_STACK_C4_END" = ("_lc_ge_STACK_C4" == 0) ? 0 : "_lc_ge_STACK_C4" - 1;
    "_STACK_C4_LIMIT" = "_lc_ge_STACK_C4";

    "_STACK_C4_ALL_START" = "_STACK_C4_START";
    "_STACK_C4_ALL_END" = "_STACK_C4_END";
    "_STACK_C4_ALL_LIMIT" = "_STACK_C4_LIMIT";
  }

  group STACK_C5_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core5)
  {
    group STACK_C5 (ordered, contiguous, fill, align = 4)
    {
      reserved "STACK_C5" (size = 1024);
    }
    group STACK_C5_PAD (align = 4)
    {
      reserved "STACK_C5_PAD" (size = 0);
    }
    "_STACK_C5_START" = "_lc_gb_STACK_C5";
    "_STACK_C5_END" = ("_lc_ge_STACK_C5" == 0) ? 0 : "_lc_ge_STACK_C5" - 1;
    "_STACK_C5_LIMIT" = "_lc_ge_STACK_C5";

    "_STACK_C5_ALL_START" = "_STACK_C5_START";
    "_STACK_C5_ALL_END" = "_STACK_C5_END";
    "_STACK_C5_ALL_LIMIT" = "_STACK_C5_LIMIT";
  }

  "_RESET" = "brsStartupEntry";
  "_start_tc5" = "brsStartupEntry";
  "_start" = "brsStartupEntry";
  "StartupEntry" = "brsStartupEntry";
  "_brsStartupEntry" = "brsStartupEntry";
  "_start_tc0" = "brsStartupEntry";
  "_start_tc1" = "brsStartupEntry";
  "_start_tc2" = "brsStartupEntry";
  "_start_tc3" = "brsStartupEntry";
  "_start_tc4" = "brsStartupEntry";

  "__STARTUPSTACK_CORE0" = "_STACK_C0_LIMIT";
  "__STARTUPSTACK_CORE1" = "_STACK_C1_LIMIT";
  "__STARTUPSTACK_CORE2" = "_STACK_C2_LIMIT";
  "__STARTUPSTACK_CORE3" = "_STACK_C3_LIMIT";
  "__STARTUPSTACK_CORE4" = "_STACK_C4_LIMIT";
  "__STARTUPSTACK_CORE5" = "_STACK_C5_LIMIT";

  group OS_CODE_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_CODE (ordered, contiguous, fill)
    {
      section "OS_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_CODE";
        select "[.]text.OS_OS_COREINITHOOK_CODE";
      }
    }
    group OS_CODE_PAD (align = 1)
    {
      reserved "OS_CODE_PAD" (size = 16);
    }
    "_OS_CODE_START" = "_lc_gb_OS_CODE";
    "_OS_CODE_END" = ("_lc_gb_OS_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_CODE_PAD" - 1;
    "_OS_CODE_LIMIT" = "_lc_gb_OS_CODE_PAD";

    "_OS_CODE_ALL_START" = "_OS_CODE_START";
    "_OS_CODE_ALL_END" = "_OS_CODE_END";
    "_OS_CODE_ALL_LIMIT" = "_OS_CODE_LIMIT";
  }

  group OS_CONST_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group OS_CONST (ordered, contiguous, fill)
    {
      section "OS_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_CONST";
        select "[.]zrodata.OS_CONST_FAST";
        select "[.]rodata.OS_CORE0_CONST";
        select "[.]zrodata.OS_CORE0_CONST_FAST";
        select "[.]rodata.OS_CORE1_CONST";
        select "[.]zrodata.OS_CORE1_CONST_FAST";
        select "[.]rodata.OS_CORE2_CONST";
        select "[.]zrodata.OS_CORE2_CONST_FAST";
        select "[.]rodata.OS_CORE3_CONST";
        select "[.]zrodata.OS_CORE3_CONST_FAST";
        select "[.]rodata.OS_CORE4_CONST";
        select "[.]zrodata.OS_CORE4_CONST_FAST";
        select "[.]rodata.OS_CORE5_CONST";
        select "[.]zrodata.OS_CORE5_CONST_FAST";
        select "[.]rodata.OS_SystemApplication_OsCore0_CONST";
        select "[.]zrodata.OS_SystemApplication_OsCore0_CONST_FAST";
        select "[.]rodata.OS_SystemApplication_OsCore1_CONST";
        select "[.]zrodata.OS_SystemApplication_OsCore1_CONST_FAST";
        select "[.]rodata.OS_SystemApplication_OsCore2_CONST";
        select "[.]zrodata.OS_SystemApplication_OsCore2_CONST_FAST";
        select "[.]rodata.OS_SystemApplication_OsCore3_CONST";
        select "[.]zrodata.OS_SystemApplication_OsCore3_CONST_FAST";
        select "[.]rodata.OS_SystemApplication_OsCore4_CONST";
        select "[.]zrodata.OS_SystemApplication_OsCore4_CONST_FAST";
        select "[.]rodata.OS_SystemApplication_OsCore5_CONST";
        select "[.]zrodata.OS_SystemApplication_OsCore5_CONST_FAST";
      }
    }
    group OS_CONST_PAD (align = 1)
    {
      reserved "OS_CONST_PAD" (size = 16);
    }
    "_OS_CONST_START" = "_lc_gb_OS_CONST";
    "_OS_CONST_END" = ("_lc_gb_OS_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_CONST_PAD" - 1;
    "_OS_CONST_LIMIT" = "_lc_gb_OS_CONST_PAD";

    "_OS_CONST_ALL_START" = "_OS_CONST_START";
    "_OS_CONST_ALL_END" = "_OS_CONST_END";
    "_OS_CONST_ALL_LIMIT" = "_OS_CONST_LIMIT";
  }

  group Const_Default_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group rodata (ordered, contiguous, fill)
    {
      section "rodata_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata*";
      }
    }
    "_rodata_START" = "_lc_gb_rodata";
    "_rodata_END" = ("_lc_ge_rodata" == 0) ? 0 : "_lc_ge_rodata" - 1;
    "_rodata_LIMIT" = "_lc_ge_rodata";

    group text (ordered, contiguous, fill)
    {
      section "text_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text*";
      }
    }
    "_text_START" = "_lc_gb_text";
    "_text_END" = ("_lc_ge_text" == 0) ? 0 : "_lc_ge_text" - 1;
    "_text_LIMIT" = "_lc_ge_text";

    group zrodata (ordered, contiguous, fill)
    {
      section "zrodata_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]zrodata*";
      }
    }
    "_zrodata_START" = "_lc_gb_zrodata";
    "_zrodata_END" = ("_lc_ge_zrodata" == 0) ? 0 : "_lc_ge_zrodata" - 1;
    "_zrodata_LIMIT" = "_lc_ge_zrodata";

    "_Const_Default_ALL_START" = "_rodata_START";
    "_Const_Default_ALL_END" = "_zrodata_END";
    "_Const_Default_ALL_LIMIT" = "_zrodata_LIMIT";
  }

  group Data_Default_ROM_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_PFlash0_Cached)
  {
    group data_ROM (ordered, contiguous, fill, align = 16)
    {
      section "data_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data*";
        }
      }
    }
    "_data_ROM_START" = "_lc_gb_data_ROM";
    "_data_ROM_LIMIT" = "_lc_ge_data_ROM";

    group zdata_ROM (ordered, contiguous, fill, align = 16)
    {
      section "zdata_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata*";
        }
      }
    }
    "_zdata_ROM_START" = "_lc_gb_zdata_ROM";
    "_zdata_ROM_LIMIT" = "_lc_ge_zdata_ROM";

  }

  group Data_Default_GROUP (ordered, contiguous, run_addr = mem:mpe:RegionBlock_0_DSPR_Core0)
  {
    group bss (ordered, contiguous, fill, align = 16)
    {
      section "bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss*";
      }
    }
    group bss_PAD (align = 4)
    {
      reserved "bss_PAD" (size = 0);
    }
    "_bss_START" = "_lc_gb_bss";
    "_bss_END" = ("_lc_ge_bss" == 0) ? 0 : "_lc_ge_bss" - 1;
    "_bss_LIMIT" = "_lc_ge_bss";

    group data (ordered, contiguous, fill, align = 16)
    {
      section "data_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data*";
      }
    }
    group data_PAD (align = 4)
    {
      reserved "data_PAD" (size = 0);
    }
    "_data_START" = "_lc_gb_data";
    "_data_END" = ("_lc_ge_data" == 0) ? 0 : "_lc_ge_data" - 1;
    "_data_LIMIT" = "_lc_ge_data";

    group zbss (ordered, contiguous, fill, align = 16)
    {
      section "zbss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss*";
      }
    }
    group zbss_PAD (align = 4)
    {
      reserved "zbss_PAD" (size = 0);
    }
    "_zbss_START" = "_lc_gb_zbss";
    "_zbss_END" = ("_lc_ge_zbss" == 0) ? 0 : "_lc_ge_zbss" - 1;
    "_zbss_LIMIT" = "_lc_ge_zbss";

    group zdata (ordered, contiguous, fill, align = 16)
    {
      section "zdata_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata*";
      }
    }
    group zdata_PAD (align = 4)
    {
      reserved "zdata_PAD" (size = 0);
    }
    "_zdata_START" = "_lc_gb_zdata";
    "_zdata_END" = ("_lc_ge_zdata" == 0) ? 0 : "_lc_ge_zdata" - 1;
    "_zdata_LIMIT" = "_lc_ge_zdata";

    "_Data_Default_ALL_START" = "_bss_START";
    "_Data_Default_ALL_END" = "_zdata_END";
    "_Data_Default_ALL_LIMIT" = "_zdata_LIMIT";
  }

}


