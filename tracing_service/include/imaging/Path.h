#ifndef IMAGING_PRIMITIVES_PATH_H
#define IMAGING_PRIMITIVES_PATH_H

#include <imaging/PathCommand.h>
#include <imaging/Primitive.h>
#include <vector>

namespace ImTrcr {
namespace Imaging {
namespace Primitives {

    class Path : public Primitive {
    public:
        Path(ArgbQuad color);
        void AddCommand(const PathCommand& command);
        const std::vector<PathCommand>& GetCommands() const;
    private:
        std::vector<PathCommand> commands;
    };

}
}
}

#endif
