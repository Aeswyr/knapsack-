
class VertexBuffer {
private:
    unsigned int RID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};

