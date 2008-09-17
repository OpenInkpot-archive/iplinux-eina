/* EINA - EFL data type library
 * Copyright (C) 2008 Cedric Bail
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library;
 * if not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "eina_suite.h"
#include "eina_mempool.h"

START_TEST(eina_mempool_init_shutdown)
{
   Eina_Module_Group *gp;
   Eina_Mempool *mp;

   eina_mempool_init();

   gp = eina_mempool_module_group_get();
   fail_if(!gp);

   eina_module_path_register(gp, PACKAGE_BUILD_DIR"/src/modules", EINA_TRUE);

   mp = eina_mempool_new("test", "test", NULL);
   fail_if(mp != NULL);

   eina_mempool_shutdown();
}
END_TEST

START_TEST(eina_mempool_chained_mempool)
{
   Eina_Module_Group *gp;
   Eina_Mempool *mp;
   int *tbl[512];
   int i;

   eina_mempool_init();

   eina_module_root_add(PACKAGE_BUILD_DIR"/src/tests");

   gp = eina_mempool_module_group_get();
   fail_if(!gp);
   eina_module_path_register(gp, PACKAGE_BUILD_DIR"/src/modules", EINA_TRUE);

   mp = eina_mempool_new("chained_mempool", "test", NULL, sizeof (int), 256);
   fail_if(!mp);

   for (i = 0; i < 512; ++i)
     {
	tbl[i] = eina_mempool_alloc(mp, sizeof (int));
	fail_if(!tbl[i]);
	*tbl[i] = i;
     }

   for (i = 0; i < 512; ++i)
     fail_if(*tbl[i] != i);

   for (i = 0; i < 256; ++i)
     eina_mempool_free(mp, tbl[i]);

   fail_if(eina_mempool_realloc(mp, tbl[500], 25) != NULL);

   eina_mempool_delete(mp);

   eina_mempool_shutdown();
}
END_TEST

START_TEST(eina_mempool_pass_through)
{
   Eina_Module_Group *gp;
   Eina_Mempool *mp;
   int *tbl[512];
   int i;

   eina_mempool_init();

   eina_module_root_add(PACKAGE_BUILD_DIR"/src/tests");

   gp = eina_mempool_module_group_get();
   fail_if(!gp);
   eina_module_path_register(gp, PACKAGE_BUILD_DIR"/src/modules", EINA_TRUE);

   mp = eina_mempool_new("pass_through", "test", NULL, sizeof (int), 8, 0);
   fail_if(!mp);

   for (i = 0; i < 512; ++i)
     {
	tbl[i] = eina_mempool_alloc(mp, sizeof (int));
	fail_if(!tbl[i]);
	*tbl[i] = i;
     }

   for (i = 0; i < 512; ++i)
     fail_if(*tbl[i] != i);

   for (i = 0; i < 256; ++i)
     eina_mempool_free(mp, tbl[i]);

   fail_if(eina_mempool_realloc(mp, tbl[500], 25) == NULL);

   eina_mempool_delete(mp);

   eina_mempool_shutdown();
}
END_TEST

#ifdef EINA_EMEMOA_SUPPORT
START_TEST(eina_mempool_ememoa_fixed)
{
   Eina_Module_Group *gp;
   Eina_Mempool *mp;
   int *tbl[512];
   int i;

   eina_mempool_init();

   eina_module_root_add(PACKAGE_BUILD_DIR"/src/tests");

   gp = eina_mempool_module_group_get();
   fail_if(!gp);
   eina_module_path_register(gp, PACKAGE_BUILD_DIR"/src/modules", EINA_TRUE);

   mp = eina_mempool_new("ememoa_fixed", "test", NULL, sizeof (int), 8, 0);
   fail_if(!mp);

   for (i = 0; i < 512; ++i)
     {
	tbl[i] = eina_mempool_alloc(mp, sizeof (int));
	fail_if(!tbl[i]);
	*tbl[i] = i;
     }

   for (i = 0; i < 512; ++i)
     fail_if(*tbl[i] != i);

   for (i = 0; i < 256; ++i)
     eina_mempool_free(mp, tbl[i]);

   fail_if(eina_mempool_realloc(mp, tbl[500], 25) != NULL);

   eina_mempool_gc(mp);
   eina_mempool_statistics(mp);

   eina_mempool_delete(mp);

   eina_mempool_shutdown();
}
END_TEST

#endif

void
eina_test_mempool(TCase *tc)
{
   tcase_add_test(tc, eina_mempool_init_shutdown);
   tcase_add_test(tc, eina_mempool_chained_mempool);
   tcase_add_test(tc, eina_mempool_pass_through);
#ifdef EINA_EMEMOA_SUPPORT
   tcase_add_test(tc, eina_mempool_ememoa_fixed);
#endif
}


