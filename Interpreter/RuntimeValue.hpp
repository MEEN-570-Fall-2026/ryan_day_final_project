#ifndef RUNTIMEVALUE
#define RUNTIMEVALUE

#include <memory>
#include <string>
#include <variant>
#include <stdexcept>

class CADObject; // Forward Declaration for compiler
class ViewerAPI;
class Mesher;
class Mesh;

class RuntimeValue {
    public:
        using CADObjectPointer = std::shared_ptr<CADObject>;
        using ViewerAPIPointer = std::shared_ptr<ViewerAPI>;
        using MesherPointer = std::shared_ptr<Mesher>;
        using MeshPointer = std::shared_ptr<Mesh>;
        using Storage = std::variant<
            std::monostate,
            int,
            double,
            bool,
            CADObjectPointer,
            ViewerAPIPointer,
            MesherPointer,
            MeshPointer
        >;

        RuntimeValue() = default;
        RuntimeValue(int value);
        RuntimeValue(double value);
        RuntimeValue(bool value);
        RuntimeValue(CADObjectPointer value);
        RuntimeValue(ViewerAPIPointer value);
        RuntimeValue(MesherPointer value);
        RuntimeValue(MeshPointer value);

        template <typename T>
        bool is() const {
            return std::holds_alternative<T>(value);
        }

        template <typename T>
        T as() const {
            if (const auto* stored = std::get_if<T>(&value)) {
                return *stored;
            }
            throw std::runtime_error("RuntimeValue type mismatch");
        }

        double as_number() const;
    

    private:
        Storage value{};
};

#endif
