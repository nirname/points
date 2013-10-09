#ifndef EXCEPTION_H
#define EXCEPTION_H 1

enum EXCEPTION {
	UNKNOWN_ERROR,
	UNKNOWN_YAML_TYPE, // for parsing yaml
	UNKNOWN_ATTRIBUTE // for parsing yaml
};

std::ostream & operator << (std::ostream & _ostream, const EXCEPTION & _exception) {
	switch(_exception) {
		case UNKNOWN_ERROR: _ostream << "Unknown error"; break;
		case UNKNOWN_YAML_TYPE: _ostream << "Unknown how to load YAML type"; break;
		case UNKNOWN_ATTRIBUTE: _ostream << "Object does not contain specified YAML attribute"; break;
		default: _ostream << "Unknown exception"; break;
	}
	return _ostream;
}

#endif
