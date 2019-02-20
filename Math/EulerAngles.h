#if !defined(ENLER_ANGLES_H)
#define ENLER_ANGLES_H

class EulerAngles
{
  public:
    float heading;
    float pitch;
    float bank;

  public:
    EulerAngles() {}
    EulerAngles(float h, float p, float b) : heading(h), pitch(p), bank(b) {}
    EulerAngles(EulerAngles &&) = default;
    EulerAngles(const EulerAngles &) = default;
    EulerAngles &operator=(EulerAngles &&) = default;
    EulerAngles &operator=(const EulerAngles &) = default;
    ~EulerAngles();

    void Identity()
    {
        pitch = bank = heading = 0.0f;
    }

    void Canonize();

  private:
};

extern const EulerAngles kEulerAnglesIdentity;

#endif // ENLER_ANGLES_H
