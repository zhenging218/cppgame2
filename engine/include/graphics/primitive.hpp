#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

namespace cppengine {
    class Primitive {
    private:

    public:
        using vertex_value_type = float;
        using vertex_array_type = vertex_value_type const *;
        using index_value_type = int;
        using index_array_type = index_value_type const *;

        virtual vertex_array_type getVertices() const = 0;
        virtual index_array_type getIndices() const = 0;

        virtual std::size_t getValueCount() const = 0;
        virtual std::size_t getIndexCount() const = 0;
        virtual std::size_t getStride() const;

        virtual ~Primitive() = 0;
    };

    inline Primitive::~Primitive() = default;
}

#endif