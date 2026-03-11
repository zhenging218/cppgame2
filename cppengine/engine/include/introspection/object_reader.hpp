#ifndef OBJECT_READER_HPP
#define OBJECT_READER_HPP

namespace cppengine {

    class ObjectReader;

    template <typename T>
    concept InspectorReadableType = requires(T const & t, ObjectReader &r) { { t.inspect(r) } -> std::same_as<void>; };

    class ObjectReader {
    private:


    protected:
        virtual void beginObject() = 0;



        virtual void endObject() = 0;

    public:

        template <typename T>
        void inspect(T const &src, ObjectReader &r);

        virtual ~ObjectReader() = 0;
    };

    inline ObjectReader::~ObjectReader() = default;
}

#endif