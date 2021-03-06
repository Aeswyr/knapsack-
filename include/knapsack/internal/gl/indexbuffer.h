class IndexBuffer {
private:
    unsigned int RID;
    unsigned int count;
public:
    IndexBuffer(const unsigned short* data, unsigned int count);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
};