#include <qpdf/QPDF_Unresolved.hh>

#include <stdexcept>

QPDF_Unresolved::QPDF_Unresolved(QPDF* qpdf, QPDFObjGen const& og) :
    QPDFValue(::ot_unresolved, "unresolved", qpdf, og)
{
}

std::shared_ptr<QPDFObject>
QPDF_Unresolved::create(QPDF* qpdf, QPDFObjGen const& og)
{
    return do_create(new QPDF_Unresolved(qpdf, og));
}

std::shared_ptr<QPDFObject>
QPDF_Unresolved::shallowCopy()
{
    throw std::logic_error(
        "attempted to shallow copy unresolved QPDFObjectHandle");
    return create(qpdf, og);
}

std::string
QPDF_Unresolved::unparse()
{
    // throw std::logic_error(
    //     "attempted to unparse an unresolved QPDFObjectHandle");
    return "null";
}

JSON
QPDF_Unresolved::getJSON(int json_version)
{
    return JSON::makeNull();
}
