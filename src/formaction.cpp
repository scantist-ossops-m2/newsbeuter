#include <formaction.h>
#include <view.h>
#include <utils.h>
#include <config.h>

namespace newsbeuter {

formaction::formaction(view * vv, std::string formstr) : v(vv), f(0), do_redraw(true) { 
	f = new stfl::form(formstr);
}

void formaction::set_keymap_hints() {
	f->set("help", prepare_keymap_hint(this->get_keymap_hint()));
}

formaction::~formaction() { 
	delete f;
}

stfl::form * formaction::get_form() {
	return f;
}

std::string formaction::prepare_keymap_hint(keymap_hint_entry * hints) {
	std::string keymap_hint;
	for (int i=0;hints[i].op != OP_NIL; ++i) {
		keymap_hint.append(v->get_keys()->getkey(hints[i].op));
		keymap_hint.append(":");
		keymap_hint.append(hints[i].text);
		keymap_hint.append(" ");
	}
	return keymap_hint;	
}

std::string formaction::get_value(const std::string& value) {
	return f->get(value);
}

void formaction::handle_cmdline(const std::string& cmdline) {
	std::vector<std::string> tokens = utils::tokenize_quoted(cmdline, " \t=");
	char buf[1024];
	configcontainer * cfg = v->get_cfg();
	assert(cfg != NULL);
	if (tokens.size() > 0) {
		std::string cmd = tokens[0];
		tokens.erase(tokens.begin());
		if (cmd == "set") {
			if (tokens.size()==0) {
				v->show_error(_("usage: set <variable>[=<value>]"));
			} else if (tokens.size()==1) {
				snprintf(buf,sizeof(buf), "  %s=%s", tokens[0].c_str(), cfg->get_configvalue(tokens[0]).c_str());
				v->set_status(buf);
			} else if (tokens.size()==2) {
				cfg->set_configvalue(tokens[0], tokens[1]);
			} else {
				v->show_error(_("usage: set <variable>[=<value>]"));
			}
		}
	}
}

}
