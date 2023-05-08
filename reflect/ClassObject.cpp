#include "ClassObject.h"

#include "ClassFactory.h"
#include "ClassMethod.h"

void Object::call(const std::string& method_name)
{
    std::cout << " m_class_name: " << m_class_name << " method: " << method_name << std::endl;
    ClassFactory* factory = Sigleton<ClassFactory>::get_instance();
    ClassMethod* method = factory->get_class_method(get_class_name(), method_name);
    assert(method != NULL);

    auto func = method->method();
    typedef std::function<void(decltype(this))> class_method;

    (*((class_method*)func))(this);
}