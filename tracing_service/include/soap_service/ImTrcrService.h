/* generated\ImTrcrService.h
   Generated by wsdl2h 2.8.8 from ..\imtrcr_soap.wsdl and typemap.dat
   2012-05-01 09:15:56 GMT

   DO NOT INCLUDE THIS FILE DIRECTLY INTO YOUR PROJECT BUILDS
   USE THE soapcpp2-GENERATED SOURCE CODE FILES FOR YOUR PROJECT BUILDS

   gSOAP XML Web services tools.
   Copyright (C) 2001-2012 Robert van Engelen, Genivia Inc. All Rights Reserved.
   Part of this software is released under one of the following licenses:
   GPL or Genivia's license for commercial use.
*/

/** @page page_notes Usage Notes

NOTE:

 - Run soapcpp2 on generated\ImTrcrService.h to generate the SOAP/XML processing logic.
   Use soapcpp2 option -I to specify paths for #import
   To build with STL, 'stlvector.h' is imported from 'import' dir in package.
   Use soapcpp2 option -i to generate improved proxy and server classes.
 - Use wsdl2h options -c and -s to generate pure C code or C++ code without STL.
 - Use 'typemap.dat' to control namespace bindings and type mappings.
   It is strongly recommended to customize the names of the namespace prefixes
   generated by wsdl2h. To do so, modify the prefix bindings in the Namespaces
   section below and add the modified lines to 'typemap.dat' to rerun wsdl2h.
 - Use Doxygen (www.doxygen.org) on this file to generate documentation.
 - Use wsdl2h options -nname and -Nname to globally rename the prefix 'ns'.
 - Use wsdl2h option -d to enable DOM support for xsd:anyType.
 - Use wsdl2h option -g to auto-generate readers and writers for root elements.
 - Struct/class members serialized as XML attributes are annotated with a '@'.
 - Struct/class members that have a special role are annotated with a '$'.

WARNING:

   DO NOT INCLUDE THIS FILE DIRECTLY INTO YOUR PROJECT BUILDS.
   USE THE SOURCE CODE FILES GENERATED BY soapcpp2 FOR YOUR PROJECT BUILDS:
   THE soapStub.h FILE CONTAINS THIS CONTENT WITHOUT ANNOTATIONS.

LICENSE:

@verbatim
--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2000-2012, Robert van Engelen, Genivia Inc. All Rights Reserved.

This software is released under one of the following two licenses:
1) GPL or 2) Genivia's license for commercial use.
--------------------------------------------------------------------------------
1) GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org

This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
2) A commercial-use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
@endverbatim

*/


//gsoapopt w

/******************************************************************************\
 *                                                                            *
 * Definitions                                                                *
 *   http://namespaces.sstu-pvs.ru/imtrcr                                     *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Import                                                                     *
 *                                                                            *
\******************************************************************************/


// STL vector containers (use option -s to remove STL dependency)
#import "stlvector.h"

/******************************************************************************\
 *                                                                            *
 * Schema Namespaces                                                          *
 *                                                                            *
\******************************************************************************/


/* NOTE:

It is strongly recommended to customize the names of the namespace prefixes
generated by wsdl2h. To do so, modify the prefix bindings below and add the
modified lines to typemap.dat to rerun wsdl2h:

ns1 = "http://namespaces.sstu-pvs.ru/imtrcr"
ns2 = "http://namespaces.sstu-pvs.ru/imtrcr/types"

*/

#define SOAP_NAMESPACE_OF_ns2	"http://namespaces.sstu-pvs.ru/imtrcr/types"
//gsoap ns2   schema namespace:	http://namespaces.sstu-pvs.ru/imtrcr/types
//gsoap ns2   schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Built-in Schema Types and Top-Level Elements and Attributes                *
 *                                                                            *
\******************************************************************************/


/// Primitive built-in type "xs:integer"
typedef std::string xsd__integer;

/******************************************************************************\
 *                                                                            *
 * Forward Declarations                                                       *
 *                                                                            *
\******************************************************************************/



//  Forward declaration of class _ns2__Trace.
class _ns2__Trace;

//  Forward declaration of class _ns2__TraceResponse.
class _ns2__TraceResponse;

/******************************************************************************\
 *                                                                            *
 * Schema Types and Top-Level Elements and Attributes                         *
 *   http://namespaces.sstu-pvs.ru/imtrcr/types                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Schema Complex Types and Top-Level Elements                                *
 *   http://namespaces.sstu-pvs.ru/imtrcr/types                               *
 *                                                                            *
\******************************************************************************/



/// Top-level root element "http://namespaces.sstu-pvs.ru/imtrcr/types":Trace

/// "http://namespaces.sstu-pvs.ru/imtrcr/types":Trace is a complexType.
class _ns2__Trace
{ public:
/// Element imageData of type xs:string.
    std::string                          imageData                      1;	///< Required element.
/// A handle to the soap struct that manages this instance (automatically set)
    struct soap                         *soap                          ;
};


/// Top-level root element "http://namespaces.sstu-pvs.ru/imtrcr/types":TraceResponse

/// "http://namespaces.sstu-pvs.ru/imtrcr/types":TraceResponse is a complexType.
class _ns2__TraceResponse
{ public:
/// Element svgXml of type xs:string.
    std::string                          svgXml                         1;	///< Required element.
/// Element statusCode of type xs:integer.
    xsd__integer                         statusCode                     1;	///< Required element.
/// A handle to the soap struct that manages this instance (automatically set)
    struct soap                         *soap                          ;
};

/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   http://namespaces.sstu-pvs.ru/imtrcr/types                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   http://namespaces.sstu-pvs.ru/imtrcr/types                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Services                                                                   *
 *                                                                            *
\******************************************************************************/


//gsoap ns1  service name:	ImTrcrSoapBinding 
//gsoap ns1  service type:	ImTrcrPortType 
//gsoap ns1  service namespace:	http://namespaces.sstu-pvs.ru/imtrcr 
//gsoap ns1  service transport:	http://schemas.xmlsoap.org/soap/http 

/** @mainpage imtrcr Definitions

@section imtrcr_bindings Service Bindings

  - @ref ImTrcrSoapBinding

@section imtrcr_more More Information

  - @ref page_notes "Usage Notes"

  - @ref page_XMLDataBinding "XML Data Binding"

  - @ref SOAP_ENV__Header "SOAP Header Content" (when applicable)

  - @ref SOAP_ENV__Detail "SOAP Fault Detail Content" (when applicable)


*/

/**

@page ImTrcrSoapBinding Binding "ImTrcrSoapBinding"

@section ImTrcrSoapBinding_operations Operations of Binding  "ImTrcrSoapBinding"

  - @ref __ns1__Trace

@section ImTrcrSoapBinding_ports Endpoints of Binding  "ImTrcrSoapBinding"

Note: use wsdl2h option -N to change the service binding prefix name

*/

/******************************************************************************\
 *                                                                            *
 * Service Binding                                                            *
 *   ImTrcrSoapBinding                                                        *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   __ns1__Trace                                                             *
 *                                                                            *
\******************************************************************************/


/// Operation "__ns1__Trace" of service binding "ImTrcrSoapBinding"

/**

Operation details:


  - SOAP document/literal style messaging

  - SOAP action: "http://namespaces.sstu-pvs.ru/imtrcr/#Trace"

  - Addressing action: "http://namespaces.sstu-pvs.ru/imtrcr/ImTrcrPortType/Trace"

  - Addressing response action: "http://namespaces.sstu-pvs.ru/imtrcr/ImTrcrPortType/TraceResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call___ns1__Trace(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    _ns2__Trace*                        ns2__Trace,
    // response parameters:
    _ns2__TraceResponse*                ns2__TraceResponse
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int __ns1__Trace(
    struct soap *soap,
    // request parameters:
    _ns2__Trace*                        ns2__Trace,
    // response parameters:
    _ns2__TraceResponse*                ns2__TraceResponse
  );
@endcode

C++ proxy class (defined in soapImTrcrSoapBindingProxy.h):
@code
  class ImTrcrSoapBindingProxy;
@endcode
Important: use soapcpp2 option '-i' to generate greatly improved and easy-to-use proxy classes;

C++ service class (defined in soapImTrcrSoapBindingService.h):
@code
  class ImTrcrSoapBindingService;
@endcode
Important: use soapcpp2 option '-i' to generate greatly improved and easy-to-use service classes;

*/

//gsoap ns1  service method-style:	Trace document
//gsoap ns1  service method-encoding:	Trace literal
//gsoap ns1  service method-action:	Trace http://namespaces.sstu-pvs.ru/imtrcr/#Trace
//gsoap ns1  service method-output-action:	Trace http://namespaces.sstu-pvs.ru/imtrcr/ImTrcrPortType/TraceResponse
int __ns1__Trace(
    _ns2__Trace*                        ns2__Trace,	///< Request parameter
    _ns2__TraceResponse*                ns2__TraceResponse	///< Response parameter
);

/******************************************************************************\
 *                                                                            *
 * XML Data Binding                                                           *
 *                                                                            *
\******************************************************************************/


/**

@page page_XMLDataBinding XML Data Binding

SOAP/XML services use data bindings contractually bound by WSDL and auto-
generated by wsdl2h and soapcpp2 (see Service Bindings). Plain data bindings
are adopted from XML schemas as part of the WSDL types section or when running
wsdl2h on a set of schemas to produce non-SOAP-based XML data bindings.

The following readers and writers are C/C++ data type (de)serializers auto-
generated by wsdl2h and soapcpp2. Run soapcpp2 on this file to generate the
(de)serialization code, which is stored in soapC.c[pp]. Include "soapH.h" in
your code to import these data type and function declarations. Only use the
soapcpp2-generated files in your project build. Do not include the wsdl2h-
generated .h file in your code.

XML content can be retrieved from:
  - a file descriptor, using soap->recvfd = fd
  - a socket, using soap->socket = ...
  - a C++ stream, using soap->is = ...
  - a buffer, using the soap->frecv() callback

XML content can be stored to:
  - a file descriptor, using soap->sendfd = fd
  - a socket, using soap->socket = ...
  - a C++ stream, using soap->os = ...
  - a buffer, using the soap->fsend() callback


@section ns2 Top-level root elements of schema "http://namespaces.sstu-pvs.ru/imtrcr/types"

  - <ns2:Trace> @ref _ns2__Trace
    @code
    // Reader (returns SOAP_OK on success):
    soap_read__ns2__Trace(struct soap*, _ns2__Trace*);
    // Writer (returns SOAP_OK on success):
    soap_write__ns2__Trace(struct soap*, _ns2__Trace*);
    @endcode

  - <ns2:TraceResponse> @ref _ns2__TraceResponse
    @code
    // Reader (returns SOAP_OK on success):
    soap_read__ns2__TraceResponse(struct soap*, _ns2__TraceResponse*);
    // Writer (returns SOAP_OK on success):
    soap_write__ns2__TraceResponse(struct soap*, _ns2__TraceResponse*);
    @endcode

*/

/* End of generated\ImTrcrService.h */