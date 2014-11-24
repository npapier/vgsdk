#include "vgdTest/ModuleTest.hpp"


#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <sbf/pkg/Module.hpp>

#define TYPE_OF_TEST(type_of_test_)			::testing::Test::RecordProperty( "type_of_test", type_of_test_ )
#define TESTED_MODULE(module_)				::testing::Test::RecordProperty( "module", module_ )
#define MODULE_DESCRIPTION(description_)	::testing::Test::RecordProperty( "description", description_ )
#define TESTED_CLASS(class_)				::testing::Test::RecordProperty( "class", class_ )
#define TESTED_METHOD(method_)				::testing::Test::RecordProperty( "method", method_ )
#define TESTED_CLASSPATH(path_)				::testing::Test::RecordProperty( "path", path_ )
#define LANGUAGE(language_)					::testing::Test::RecordProperty( "language", language_ )



void testInfos(const char *className, const char *methodName, const char *classPath, const char *type_of_test, const char *language)
{
	const std::string& module_name = sbf::pkg::Module::get( "vgd", "0-5" )->getName();
	std::string module_description = sbf::pkg::Module::get()->getDescription();
	boost::filesystem::path initial_path = boost::filesystem::current_path();
	initial_path = initial_path.parent_path();
	boost::filesystem::path sourcePath( initial_path / "include" / module_name / classPath );

	TYPE_OF_TEST(type_of_test);
	TESTED_MODULE(module_name.c_str());
	MODULE_DESCRIPTION(module_description.c_str());
	TESTED_CLASS(className);
	TESTED_METHOD(methodName);
	TESTED_CLASSPATH(sourcePath.string().c_str());
	LANGUAGE(language);	
}
