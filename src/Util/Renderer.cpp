#include "Renderer.h"

#include "BresenhamLine.h"

struct SimpleVec2D
{
    float x;
    float y;

    static float DotProduct(SimpleVec2D vec1, SimpleVec2D vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }
};

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
    std::vector<BresenhamPoint> points;
    
    BresenhamLineCaseA(x1, y1, x2, y2, &points);

    for (auto& point : points)
    {
        SetPixel(hdc, point.x, point.y, RGB(255, 0, 0));
    }

    wchar_t str[256];
    swprintf_s(str, L"Number Of Pixels : %d", points.size());

    TextOut(hdc, 10, 10, str, wcslen(str));
}

void DrawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3)
{
    int minX = x1;
    int maxX = x1;

    int minY = y1;
    int maxY = y1;

    // x
    // -----
    if (minX > x2)
    {
        minX = x2;
    }

    if (minX > x3)
    {
        minX = x3;
    }

    if (maxX < x2)
    {
        maxX = x2;
    }

    if (maxX < x3)
    {
        maxX = x3;
    }

    // y
    // -----
    if (minY > y2)
    {
        minY = y2;
    }

    if (minY > y3)
    {
        minY = y3;
    }

    if (maxY < y2)
    {
        maxY = y2;
    }

    if (maxY < y3)
    {
        maxY = y3;
    }

    // Do Compute
    // -----
    SimpleVec2D u;
    {
        u.x = x1 - x3;
        u.y = y1 - y3;
    }

    SimpleVec2D v;
    {
        v.x = x2 - x3;
        v.y = y2 - y3;
    }

    float uu = SimpleVec2D::DotProduct(u, u);
    float vv = SimpleVec2D::DotProduct(v, v);
    float uv = SimpleVec2D::DotProduct(u, v);

    float wv;
    float wu;

    float divider = (uv * uv) - (uu * vv); // (uv)^2 - (uu)(uv)

    float s;
    float t;

    int pixelCnt = 0;

    // Draw a triangle.
    // -----
    for (int y = minY; y <= maxY; y++)
    {
        SimpleVec2D w;
        {
            w.y = y - y3;
            w.x = minX - x3;
        }

        for (int x = minX; x <= maxX; x++, w.x++)
        {
            wv = SimpleVec2D::DotProduct(w, v);
            wu = SimpleVec2D::DotProduct(w, u);
            
            t = ((wu * uv) - (wv * uu)) / divider;
            s = ((wv * uv) - (wu * vv)) / divider;

            // Check that the point is located in the barycentric coordinate.
            // -----
            if (0.f < t && t < 1.f && 0.f < s && s < 1.f &&
                0.f < t + s && t + s < 1.f)
            {
                SetPixel(hdc, x, y, RGB(255 * s, 255 * t, 255 * (1 - (t + s))));

                pixelCnt++;
            }
        }
    }

    wchar_t str[256];
    swprintf_s(str, L"Number Of Pixels : %d", pixelCnt);

    TextOut(hdc, 10, 10, str, wcslen(str));
}
