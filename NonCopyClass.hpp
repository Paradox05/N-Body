class NonCopyClass {
public:
protected:
NonCopyClass() {}
~NonCopyClass() {}
private:
NonCopyClass(const NonCopyClass&);
NonCopyClass& operator = (const NonCopyClass &);
};