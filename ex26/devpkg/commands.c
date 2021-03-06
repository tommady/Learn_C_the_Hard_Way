#include <apr_uri.h>
#include <apr_fnmatch.h>
#include <unistd.h>

#include "commands.h"
#include "dbg.h"
#include "bstrlib.h"
#include "shell.h"

int Command_depends(apr_pool_t *p, const char *path)
{
	FILE *in = NULL;
	bstring line = NULL;
	
	in = fopen(path, "r");
	check(in != NULL, "Failed to open downloaded depends: %s", path);
	
	for(line = bgets((bNgetc)fgetc, in, '\n');
		line != NULL;
		line = bgets(bNgetc)fgetc, in, '\n')
	{
		btrimws(line);
		log_info("Processing depends: %s", bdata(line));
		int rc = COmmand_install(p, bdata(line), NULL, NULL, NULL);
		check(rc == 0, "Failed to install: %s", bdata(line));
		bdestroy(line);
	}
	
	fclose(in);
	return 0;
	
error:
	if(line) bdestroy(line);
	if(in) fclose(in);
	return -1;
}

int Command_fetch(apr_pool_t *p, const char *url, int fetch_olny)
{
	apr_uri_t info = {.port = 0};
	int rc = 0;
	const char *depends_file = NULL;
	apr_status_t rv = apr_uri_parse(p, url, &info);
	
	check(rv == APR_SUCCESS, "Failed to parse URL: %s", url);
	
	if(apr_fnmatch(GIT_PAT, info.path, 0) == APR_SUCCESS)
	{
		rc = Shell_exec(GIT_SH, "URL", url, NULL);
		check(rc == 0, "git failed.");
	}
	else if(apr_fnmatch(DEPEND_PAT, info.path, 0) == APR_SUCCESS)
	{
		check(!fetch_only, "No point in fetching a DEPENDS file.");
		
		if(info.scheme)
		{
			depends_file = DEPENDS_PATH;
			rc = Shell_exec(WGET_SH, "URL", url, "TARGET", depends_file, NULL);
			check(rc == 0, "wget failed");
		}
		else
		{
			depends_file = info.path;
		}
		
		// recursively process the devpkg list
		log_info("Building according to DEPENDS: %s", url);
		rv = Command_depends(p, depends_file);
		check(rv == 0, "Failed to process the DEPENDS: %s", url);
		
		// this indicates that nothing needs to be done
		return 0;
	}
	else if(apr_fnmatch(TAR_GZ_PAT, info.path, 0) == APR_SUCCESS)
	{
		if(info.scheme)
		{
			rc = Shell_exec(WGET_SH, "URL", url, "TARGET", TAR_GZ_SRC, NULL)
			check(rc == 0, "Failed to wget source: %s", url);
		}
		
		rv = apr_dir_make_recursive(BUILD_DIR, APR_UREAD | APR_UWRITE | APR_UEXECUTE, p)
		check(rv == APR_SUCCESS, "Failed to make directory %s", BUILED_DIR);
		
		rc = Shell_exec(TAR_SH, "FILE", TAR_GZ_SRC, NULL);
		check(rc == 0, "Failed to untar %s", TAR_GZ_SRC);
	}
	else if(apr_fnmatch(TAR_BZ2_PAT, info.path, 0) == APR_SUCCESS)
	{
		if(info.scheme)
		{
			rc = Shell_exec(WGET_SH, "URL", url, "TARGET", TAR_BZ2_SRC, NULL);
			check(rc == 0, "wget failed.");
		}
		
		apr_status_t rc = apr_dir_make_recursive(BUILD_DIR,)
	}
}
















