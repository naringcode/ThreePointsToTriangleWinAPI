#include "BresenhamLine.h"

#include <algorithm>

void BresenhamLineCaseA(int x1, int y1, int x2, int y2, std::vector<BresenhamPoint>* outPoints)
{
    int x;
    int y;

    int endX;
    int endY;

    int width  = abs(x2 - x1); // dx
    int height = abs(y2 - y1); // dy

    int doubleWidth  = width  + width;
    int doubleHeight = height + height;

    int determinant;
    int incrementor = 1;

    if (width > height)
    {
        // ���Ⱑ �ϸ��ϸ�(1���� ������) �����̴�.
        // �� ��쿡�� x���� �������� p���� üũ�ؼ� y�� �������Ѿ� �Ѵ�.
        // -----

        // �Ⱥи� ���� ������ �ش��ϴ� ��ġ�� �� 1�Ⱥи�, �� 4�Ⱥи�, �� 5�Ⱥи�, �� 8�Ⱥи��̴�.
        // -----
        
        // ó�� ������ x�� ���� �����̱� ������ x���� ���� ���� �������� ��´�.
        if (x1 < x2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // 1) �� 4�Ⱥи��� �� 8�Ⱥи鿡 ��ġ��Ų��.
            // 2) �� 5�Ⱥи��� �� 1�Ⱥи鿡 ��ġ��Ų��.
            // -----
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // dy�� �������� ��Ȳ(abs()�� �����Ű�� dy�� x�� ��Ī�� �Ǳ� ������ incrementor�� ��Ī���Ѿ� �Ѵ�.)
        if (endY - y < 0)
        {
            incrementor = -1;
        }

        determinant = doubleHeight - width; // p0 = 2dy - dx

        while (x <= endX)
        {
            BresenhamPoint p{ x, y };
            outPoints->emplace_back(p);

            x++;

            if (determinant < 0)
            {
                determinant = determinant + doubleHeight; // pnext = pk + 2dy
            }
            else
            {
                determinant = determinant + doubleHeight - doubleWidth; // pnext = pk + 2dy - 2dx

                y += incrementor;
            }
        }
    }
    else
    {
        // ���Ⱑ ���ĸ���(1���� ũ��) �а��̴�.
        // �� ��쿡�� y���� �������� p���� üũ�ؼ� x�� �������Ѿ� �Ѵ�.
        // -----

        // �Ⱥи� ���� �а��� �ش��ϴ� ��ġ�� �� 2�Ⱥи�, �� 3�Ⱥи�, �� 6�Ⱥи�, �� 7�Ⱥи��̴�.
        // -----

        // ó�� ������ y�� ���� �����̱� ������ x���� ���� ���� �������� ��´�.
        if (y1 < y2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // 1) �� 3�Ⱥи��� �� 7�Ⱥи鿡 ��ġ��Ų��.
            // 2) �� 6�Ⱥи��� �� 2�Ⱥи鿡 ��ġ��Ų��.
            // -----
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // dx�� �������� ��Ȳ(abs()�� �����Ű�� dx�� y�� ��Ī�� �Ǳ� ������ incrementor�� ��Ī���Ѿ� �Ѵ�.)
        if (endX - x < 0)
        {
            incrementor = -1;
        }

        determinant = doubleWidth - height; // p0 = 2dx - dy

        while (y <= endY)
        {
            BresenhamPoint p{ x, y };
            outPoints->emplace_back(p);

            y++;

            if (determinant < 0)
            {
                determinant = determinant + doubleWidth; // pnext = pk + 2dx
            }
            else
            {
                determinant = determinant + doubleWidth - doubleHeight; // pnext = pk + 2dx - 2dy

                x += incrementor;
            }
        }
    }
}

void BresenhamLineCaseB(int x1, int y1, int x2, int y2, std::vector<BresenhamPoint>* outPoints)
{
    // �׻� �Ⱥи��� ���ø���.
    // -----
    int width  = abs(x2 - x1); // dx
    int height = abs(y2 - y1); // dy

    int doubleWidth  = width  + width;
    int doubleHeight = height + height;

    int compX;
    int compY;

    int x;
    int y;

    int endX;
    int endY;

    int incrementor = 1;

    if (width > height)
    {
        // �Ⱥи� ���� ������ �ش��ϴ� ��ġ�� �� 1�Ⱥи�, �� 4�Ⱥи�, �� 5�Ⱥи�, �� 8�Ⱥи��̴�.
        // -----

        // ó�� ������ x�� ���� �����̱� ������ x���� ���� ���� �������� ��´�.
        if (x1 < x2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // 1) �� 4�Ⱥи��� �� 8�Ⱥи鿡 ��ġ��Ų��.
            // 2) �� 5�Ⱥи��� �� 1�Ⱥи鿡 ��ġ��Ų��.
            // -----
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // ���Ⱑ ������ ��Ȳ
        if (endY - y < 0)
        {
            incrementor = -1;
        }

        // ���Ⱑ �ϸ��Ͽ� ������ �̷��.
        // -----
        compX = width;
        compY = doubleHeight; // 2h

        while (x <= endX)
        {
            BresenhamPoint p{ x, y };
            outPoints->emplace_back(p);

            x++;

            if (compY - compX < 0)
            {
                // ���� �̵� -> 2h ����
                compY += doubleHeight;
            }
            else
            {
                // ���� �̵� �� �Ʒ��� �� ĭ -> 2h - 2w ����
                compY += doubleHeight;
                compX += doubleWidth; // dy - dx�� �ᱹ ���� ������ �������� ����

                y += incrementor;
            }
        }
    }
    else
    {
        // �Ⱥи� ���� �а��� �ش��ϴ� ��ġ�� �� 2�Ⱥи�, �� 3�Ⱥи�, �� 6�Ⱥи�, �� 7�Ⱥи��̴�.
        // -----

        // ó�� ������ y�� ���� �����̱� ������ x���� ���� ���� �������� ��´�.
        if (y1 < y2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // 1) �� 3�Ⱥи��� �� 7�Ⱥи鿡 ��ġ��Ų��.
            // 2) �� 6�Ⱥи��� �� 2�Ⱥи鿡 ��ġ��Ų��.
            // -----
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // ���Ⱑ ������ ��Ȳ
        if (endX - x < 0)
        {
            incrementor = -1;
        }

        // ���Ⱑ ���Ķ� �а��� �̷��.
        // -----
        compX = doubleWidth; // 2w
        compY = height;

        while (y <= endY)
        {
            BresenhamPoint p{ x, y };
            outPoints->emplace_back(p);
    
            y++;

            if (compX - compY < 0)
            {
                // ���� �̵� -> 2w ����
                compX += doubleWidth;
            }
            else
            {
                // ���� �̵� �� �Ʒ��� �� ĭ -> 2w - 2h ����
                compX += doubleWidth;
                compY += doubleHeight; // dx - dy�� �ᱹ ���� ������ �������� ����
    
                x += incrementor;
            }
        }
    }
}
