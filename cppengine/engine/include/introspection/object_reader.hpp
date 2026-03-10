#ifndef OBJECT_READER_HPP
#define OBJECT_READER_HPP

namespace cppengine {

    class ObjectReader;

    template <typename T>
    concept InspectorReadableType = requires(T const & t, ObjectReader &r) { { t.inspect(r) } -> std::same_as<void>; };

    class ObjectReader {
    private:


    protected:


    public:

        virtual ~ObjectReader() = 0;
    };

    inline ObjectReader::~ObjectReader() = default;
}

#endif