#ifndef PLANET_PLANET__H
#define PLANET_PLANET__H

#include <cache.h>
#include <urlreader.h>
#include <configcontainer.h>
#include <rss.h>
#include <vector>

namespace nbplanet {

class planet {
	public:
		planet();
		~planet();
		void run(int argc, char * argv[]);
	private:
		void usage(char * argv0);

		void reload_all();
		void reload(unsigned int pos);

		newsbeuter::cache * rsscache;
		newsbeuter::configcontainer * cfg;
		newsbeuter::urlreader urlcfg;
		std::vector<newsbeuter::rss_feed> feeds;

		std::string config_dir;
		std::string config_file;
		std::string url_file;
		std::string cache_file;
		std::string template_file;

		unsigned int verbose;
};

}

#endif
