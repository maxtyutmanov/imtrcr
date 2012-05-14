#include <imaging/Path.h>

using namespace std;

namespace ImTrcr {
namespace Imaging {
namespace Primitives {

    Path::Path(ArgbQuad color)
        : ImTrcr::Imaging::Primitive(color, PrimitiveType::Path) {
    }

    void Path::AddCommand(const PathCommand& command) {
        commands.push_back(command);
    }

    const vector<PathCommand>& Path::GetCommands() const {
        return commands;
    }
}
}
}
