#include <imaging/SvgSerializer.h>
#include <imaging/PathSerializer.h>
#include <utils/String.h>
#include <stdexcept>
#include <iomanip>

using namespace std;
using namespace ImTrcr::Utils;
using namespace ImTrcr::Imaging::Primitives;

namespace ImTrcr {
namespace Imaging {

    TiXmlDocument* SvgSerializer::Serialize(const Imaging::VectorImage& vectorImage) const {
        TiXmlDocument* svgXml = new TiXmlDocument();

        //<svg xmlns="http://www.w3.org/2000/svg" version="1.1">
        TiXmlElement rootEl("svg");
        rootEl.SetAttribute("xmlns", "http://www.w3.org/2000/svg");
        rootEl.SetAttribute("version", "1.1");

        const vector<Primitive*>& allPrimitives = vectorImage.GetPrimitives();
        vector<Primitive*>::const_iterator it;

        for (it = allPrimitives.begin(); it != allPrimitives.end(); ++it) {
            Primitive* pPrimitive = *it;

            switch (pPrimitive->GetType()) {
            case PrimitiveType::Path:
                rootEl.InsertEndChild(SerializePathPrimitive((Path*)pPrimitive));
                break;
            default:
                throw logic_error("Unknown type of primitive");
            }
        }

        svgXml->InsertEndChild(rootEl);

        return svgXml;
    }

    //<path d="M150 0 L75 200 L225 200 Z" />
    TiXmlElement SvgSerializer::SerializePathPrimitive(Primitives::Path* pPath) const {
        vector<PathCommand> commands = pPath->GetCommands();
        vector<PathCommand>::const_iterator it;

        string d = "";

        for (it = commands.begin(); it != commands.end(); ++it) {
            PathCommand cmd = *it;

            PathSerializer pathSerializer;

            switch (cmd.GetType()) {
            case PathCommand::MoveTo:
                pathSerializer.MoveTo(cmd);
                break;
            case PathCommand::QuadraticBezierTo:
                pathSerializer.QuadraticBezier(cmd);
                break;
            case PathCommand::CubicBezier:
                pathSerializer.CubicBezier(cmd);
                break;
            case PathCommand::ClosePath:
                pathSerializer.ClosePath();
                break;
            case PathCommand::LineTo:
                pathSerializer.LineTo(cmd);
                break;
            default:
                throw logic_error("Unknown type of path command");
                break;
            }

            string serializedCmd = pathSerializer.GetResult();

            d.append(serializedCmd.begin(), serializedCmd.end());
            d.append(1, ' ');
        }
        
        Utils::StringUtils::TrimEnd(d);

        TiXmlElement pathEl("path");

        pathEl.SetAttribute("d", d.c_str());
        
        //TODO: rewrite

        if (pPath->GetStrokeColor() == ArgbQuad::Black()) {
            pathEl.SetAttribute("fill", "#000");
        }
        else {
            pathEl.SetAttribute("fill", "#fff");
        }
        

        return pathEl;
    }

}
}
