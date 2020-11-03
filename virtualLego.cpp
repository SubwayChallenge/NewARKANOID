////////////////////////////////////////////////////////////////////////////////
//
// File: virtualLego.cpp
//
// Original Author: ��â�� Chang-hyeon Park, 
// Modified by Bong-Soo Sohn and Dong-Jun Kim
// 
// Originally programmed for Virtual LEGO. 
// Modified later to program for Virtual Billiard.
//        
////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cassert>

IDirect3DDevice9* Device = NULL;

// window size
const int Width  = 1024;
const int Height = 800;

// There are four balls
// initialize the position (coordinate) of each ball (ball0 ~ ball3)
// ����� ��ġ�� �� ���� �þ�� �� �÷����Ѵ�.�Ʒ� for ���� i�� ��� �� ������ŭ.
// sphere�� �˻��ϸ� ����
//const float spherePos[5][2] = { {-1.7f,0} , {-1.25f,0} , {-0.8f,0} , {-0.35f,0} , {0.1f,0}};

//1�� ������ ���� �׸��� ������ �� �׷�����! �̷��� �׸��� �� 57��
static int smile[14][14]{
	0,0,0,1,1,1,1,1,1,1,1,0,0,0,
	0,0,1,0,0,0,0,0,0,0,0,1,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,1,0,0,0,1,1,1,1,0,0,0,1,0,
	0,1,0,0,1,0,0,0,0,1,0,0,1,0,
	0,1,0,1,0,0,0,0,0,0,1,0,1,0,
	0,1,0,0,0,0,1,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,1,0,1,0,1,0,0,1,0,1,0,1,0,
	0,1,0,0,1,0,0,0,0,1,0,0,1,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,0,1,0,0,0,0,0,0,0,0,1,0,0,
	0,0,0,1,1,1,1,1,1,1,1,0,0,0
};


// -----------------------------------------------------------------------------
// Transform matrices
// -----------------------------------------------------------------------------
D3DXMATRIX g_mWorld;
D3DXMATRIX g_mView;
D3DXMATRIX g_mProj;

#define M_RADIUS 0.18   // ball radius
#define PI 3.14159265
#define M_HEIGHT 0.01
#define DECREASE_RATE 0.9982

// -----------------------------------------------------------------------------
// CSphere class definition
// -----------------------------------------------------------------------------

class CSphere {
private :
	float					center_x, center_y, center_z;
    float                   m_radius;
	float					m_velocity_x;
	float					m_velocity_z;

public:
    CSphere(void)
    {
        D3DXMatrixIdentity(&m_mLocal);
        ZeroMemory(&m_mtrl, sizeof(m_mtrl));
        m_radius = 0;
		m_velocity_x = 0;
		m_velocity_z = 0;
        m_pSphereMesh = NULL;
    }
    ~CSphere(void) {}

public:
    bool create(IDirect3DDevice9* pDevice, D3DXCOLOR color = d3d::WHITE)
    {
        if (NULL == pDevice)
            return false;
		
        m_mtrl.Ambient  = color; 
        m_mtrl.Diffuse  = color;
        m_mtrl.Specular = color;
        m_mtrl.Emissive = d3d::BLACK;
        m_mtrl.Power    = 5.0f;
		
        if (FAILED(D3DXCreateSphere(pDevice, getRadius(), 50, 50, &m_pSphereMesh, NULL)))
            return false;
        return true;
    }
	
    void destroy(void)
    {
        if (m_pSphereMesh != NULL) {
            m_pSphereMesh->Release();
            m_pSphereMesh = NULL;
        }
    }

    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
    {
        if (NULL == pDevice)
            return;
        pDevice->SetTransform(D3DTS_WORLD, &mWorld);
        pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
        pDevice->SetMaterial(&m_mtrl);
		m_pSphereMesh->DrawSubset(0);
    }
	
    bool hasIntersected(CSphere& ball) 
	{
		// Insert your code here.
		//���� ���� ������� �ε����� �� return true

		//���� ���� �Ͼ� ���� �ε����� �� return true
		/*D3DXVECTOR3 r_coord = g_moving_redball.getCenter();
		D3DXVECTOR3 w_coord = g_target_whiteball.getCenter();

		if (r_coord.z - M_RADIUS == w_coord.z + M_RADIUS) {
			return true;
		}*/
		
		return false;
	} 
	
	void hitBy(CSphere& ball) {
		//�̷� �������� ���� �� �� ������ getCenter �ȵ�
		/*
		https://m.blog.naver.com/PostView.nhn?blogId=caminq&logNo=100133230971&proxyReferer=https:%2F%2Fwww.google.co.kr%2F
		
		D3DXVECTOR3 coord = ball.getCenter();

		if (tX >= (2.56f - M_RADIUS))
			tX = 2.56f - M_RADIUS;
		else if (tX <= (-2.56f + M_RADIUS))
			tX = -2.56f + M_RADIUS;
		else if (tZ <= (-6.99f + M_RADIUS))
			tZ = -5.09f + M_RADIUS;
		else if (tZ >= (3.99f - M_RADIUS))
			tZ = 3.99f - M_RADIUS;


		if (block_array[x][y] == 1) { //���� ���� �ε�ĥ ���
			if (x >= 0 && y == 0) {   //���� ���� �ε����� ��
				ay *= (-1);
				y = y + ay + ay;
			}
			if (x >= 0 && y == 13) {  //������ ���� �ε����� ��
				ay *= (-1);
				y = y + ay + ay;
			}
		}
		*/
		
		// hasIntersected==true �� ��
		//if (hasIntersected) {
			// ���� ���� ������� �ε����� ��

			// ���� ���� �Ͼ� ���� �ε����� ��

		//}

	}

	void ballUpdate(float timeDiff) 
	{
		const float TIME_SCALE = 3.3;
		D3DXVECTOR3 cord = this->getCenter();
		double vx = abs(this->getVelocity_X());
		double vz = abs(this->getVelocity_Z());

		if(vx > 0.01 || vz > 0.01)
		{
			float tX = cord.x + TIME_SCALE*timeDiff*m_velocity_x;
			float tZ = cord.z + TIME_SCALE*timeDiff*m_velocity_z;

			//correction of position of ball
			//Please uncomment this part because this correction of ball position is necessary when a ball collides with a wall
			//�� �浹�� ���� �Ϸ�

			if(tX >= (2.56f - M_RADIUS))
				tX = 2.56f - M_RADIUS;
			else if(tX <=(-2.56f + M_RADIUS))
				tX = -2.56f + M_RADIUS;
			else if(tZ <= (-6.99f + M_RADIUS))
				tZ = -5.09f + M_RADIUS;
			else if(tZ >= (3.99f - M_RADIUS))
				tZ = 3.99f - M_RADIUS;
			
			this->setCenter(tX, cord.y, tZ);
		}
		else { this->setPower(0,0);}
		//this->setPower(this->getVelocity_X() * DECREASE_RATE, this->getVelocity_Z() * DECREASE_RATE);
		double rate = 1 -  (1 - DECREASE_RATE)*timeDiff * 400;
		if(rate < 0 )
			rate = 0;
		this->setPower(getVelocity_X() * rate, getVelocity_Z() * rate);
	}

	double getVelocity_X() { return this->m_velocity_x;	}
	double getVelocity_Z() { return this->m_velocity_z; }

	void setPower(double vx, double vz)
	{
		this->m_velocity_x = vx;
		this->m_velocity_z = vz;
	}

	void setCenter(float x, float y, float z)
	{
		D3DXMATRIX m;
		center_x=x;	center_y=y;	center_z=z;
		D3DXMatrixTranslation(&m, x, y, z);
		setLocalTransform(m);
	}
	
	float getRadius(void)  const { return (float)(M_RADIUS);  }
    const D3DXMATRIX& getLocalTransform(void) const { return m_mLocal; }
    void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
    D3DXVECTOR3 getCenter(void) const
    {
        D3DXVECTOR3 org(center_x, center_y, center_z);
        return org;
    }
	
private:
    D3DXMATRIX              m_mLocal;
    D3DMATERIAL9            m_mtrl;
    ID3DXMesh*              m_pSphereMesh;
	
};


// -----------------------------------------------------------------------------
// CWall class definition
// -----------------------------------------------------------------------------

class CWall {

private:
	
    float					m_x;
	float					m_z;
	float                   m_width;
    float                   m_depth;
	float					m_height;
	
public:
    CWall(void)
    {
        D3DXMatrixIdentity(&m_mLocal);
        ZeroMemory(&m_mtrl, sizeof(m_mtrl));
        m_width = 0;
        m_depth = 0;
        m_pBoundMesh = NULL;
    }
    ~CWall(void) {}
public:
    bool create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color = d3d::WHITE)
    {
        if (NULL == pDevice)
            return false;
		
        m_mtrl.Ambient  = color;
        m_mtrl.Diffuse  = color;
        m_mtrl.Specular = color;
        m_mtrl.Emissive = d3d::BLACK;
        m_mtrl.Power    = 5.0f;
		
        m_width = iwidth;
        m_depth = idepth;
		
        if (FAILED(D3DXCreateBox(pDevice, iwidth, iheight, idepth, &m_pBoundMesh, NULL)))
            return false;
        return true;
    }
    void destroy(void)
    {
        if (m_pBoundMesh != NULL) {
            m_pBoundMesh->Release();
            m_pBoundMesh = NULL;
        }
    }
    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
    {
        if (NULL == pDevice)
            return;
        pDevice->SetTransform(D3DTS_WORLD, &mWorld);
        pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
        pDevice->SetMaterial(&m_mtrl);
		m_pBoundMesh->DrawSubset(0);
    }
	
	bool hasIntersected(CSphere& ball) 
	{
		// Insert your code here. ���� �����ؼ� �Ȱ��� ���� ��.

		return false;
	}

	void hitBy(CSphere& ball) 
	{
		// Insert your code here.���� �����ؼ� �Ȱ��� ���� ��.
	}    
	
	void setPosition(float x, float y, float z)
	{
		D3DXMATRIX m;
		this->m_x = x;
		this->m_z = z;

		D3DXMatrixTranslation(&m, x, y, z);
		setLocalTransform(m);
	}
	
    float getHeight(void) const { return M_HEIGHT; }
	
	
private :
    void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
	
	D3DXMATRIX              m_mLocal;
    D3DMATERIAL9            m_mtrl;
    ID3DXMesh*              m_pBoundMesh;
};

// -----------------------------------------------------------------------------
// CLight class definition
// -----------------------------------------------------------------------------

class CLight {
public:
    CLight(void)
    {
        static DWORD i = 0;
        m_index = i++;
        D3DXMatrixIdentity(&m_mLocal);
        ::ZeroMemory(&m_lit, sizeof(m_lit));
        m_pMesh = NULL;
        m_bound._center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_bound._radius = 0.0f;
    }
    ~CLight(void) {}
public:
    bool create(IDirect3DDevice9* pDevice, const D3DLIGHT9& lit, float radius = 0.1f)
    {
        if (NULL == pDevice)
            return false;
        if (FAILED(D3DXCreateSphere(pDevice, radius, 10, 10, &m_pMesh, NULL)))
            return false;
		
        m_bound._center = lit.Position;
        m_bound._radius = radius;
		
        m_lit.Type          = lit.Type;
        m_lit.Diffuse       = lit.Diffuse;
        m_lit.Specular      = lit.Specular;
        m_lit.Ambient       = lit.Ambient;
        m_lit.Position      = lit.Position;
        m_lit.Direction     = lit.Direction;
        m_lit.Range         = lit.Range;
        m_lit.Falloff       = lit.Falloff;
        m_lit.Attenuation0  = lit.Attenuation0;
        m_lit.Attenuation1  = lit.Attenuation1;
        m_lit.Attenuation2  = lit.Attenuation2;
        m_lit.Theta         = lit.Theta;
        m_lit.Phi           = lit.Phi;
        return true;
    }
    void destroy(void)
    {
        if (m_pMesh != NULL) {
            m_pMesh->Release();
            m_pMesh = NULL;
        }
    }
    bool setLight(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
    {
        if (NULL == pDevice)
            return false;
		
        D3DXVECTOR3 pos(m_bound._center);
        D3DXVec3TransformCoord(&pos, &pos, &m_mLocal);
        D3DXVec3TransformCoord(&pos, &pos, &mWorld);
        m_lit.Position = pos;
		
        pDevice->SetLight(m_index, &m_lit);
        pDevice->LightEnable(m_index, TRUE);
        return true;
    }

    void draw(IDirect3DDevice9* pDevice)
    {
        if (NULL == pDevice)
            return;
        D3DXMATRIX m;
        D3DXMatrixTranslation(&m, m_lit.Position.x, m_lit.Position.y, m_lit.Position.z);
        pDevice->SetTransform(D3DTS_WORLD, &m);
        pDevice->SetMaterial(&d3d::WHITE_MTRL);
        m_pMesh->DrawSubset(0);
    }

    D3DXVECTOR3 getPosition(void) const { return D3DXVECTOR3(m_lit.Position); }

private:
    DWORD               m_index;
    D3DXMATRIX          m_mLocal;
    D3DLIGHT9           m_lit;
    ID3DXMesh*          m_pMesh;
    d3d::BoundingSphere m_bound;
};


// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
CWall	g_legoPlane;
CWall	g_legowall[4];
CSphere	g_sphere[57]; //Yellow ball
CSphere	g_target_whiteball;
CSphere g_moving_redball; //�����̴� ���� �� ����
CLight	g_light;
static bool isReset = true;

double g_camera_pos[3] = {0.0, 5.0, -12.0};

// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------


void destroyAllLegoBlock(void)
{

}

// Gameboard initialization
bool Setup()
{
	int i, j, k=0;
	
    D3DXMatrixIdentity(&g_mWorld);
    D3DXMatrixIdentity(&g_mView);
    D3DXMatrixIdentity(&g_mProj);
		
	// create plane and set the position
    if (false == g_legoPlane.create(Device, -1, -1, 6, 0.03f, 8, d3d::BLACK)) return false;
    g_legoPlane.setPosition(0.0f, -0.0006f / 5, 0.0f);
	
	// create walls and set the position. note that there are four walls
	if (false == g_legowall[0].create(Device, -1, -1, 6.25f, 0.3f, 0.12f, d3d::CYAN)) return false;
	g_legowall[0].setPosition(0.0f, 0.12f, 3.99f);
	if (false == g_legowall[1].create(Device, -1, -1, 6.25f, 0.3f, 0.12f, d3d::CYAN)) return false;//�Ʒ��� ���� ���� �� ���̴� ��� �ٷ� �Ʒ��� ��ġ : �ε����� �� respawn ����
	g_legowall[1].setPosition(0.0f, 0.12f, -4.99f);
	if (false == g_legowall[2].create(Device, -1, -1, 0.12f, 0.3f, 7.98f, d3d::CYAN)) return false;
	g_legowall[2].setPosition(3.f, 0.12f, 0.0f);
	if (false == g_legowall[3].create(Device, -1, -1, 0.12f, 0.3f, 7.98f, d3d::CYAN)) return false;
	g_legowall[3].setPosition(-3.f, 0.12f, 0.0f);

	// �� ����. create 5 balls and set the position
	/*for (i=0;i<5;i++) {
		if (false == g_sphere[i].create(Device, d3d::YELLOW)) return false;
		g_sphere[i].setCenter(spherePos[i][0], (float)M_RADIUS , spherePos[i][1]);
		g_sphere[i].setPower(0,0);
	}*/
	
	// smile �迭�� �� ����
	for (i = 0; i < 14; i++) {
		for (j = 0; j < 14; j++) {
			if (smile[i][j] != 0) {
				if (false == g_sphere[k].create(Device, d3d::YELLOW)) return false;
				g_sphere[k].setCenter(-2.3f+j*0.36f, (float)M_RADIUS, -2.f+i*0.36);
				g_sphere[k].setPower(0, 0);
				k++;
			}
		}
	}

	// create white ball for set direction  ���콺 Ŀ�� ������ ���󰡴� �� �ʱ�ȭ ������ �ϴ� �� �������� ����
    if (false == g_target_whiteball.create(Device, d3d::WHITE)) return false;
	g_target_whiteball.setCenter(-2.96f, (float)M_RADIUS , -3.95f);
	g_target_whiteball.setPower(0, 0);


	if (false == g_moving_redball.create(Device, d3d::RED)) return false;
	D3DXVECTOR3 startpos = g_target_whiteball.getCenter();
	g_moving_redball.setCenter(startpos.x, (float)M_RADIUS, startpos.z+((float)M_RADIUS*2));
	g_moving_redball.setPower(0, 0);
	
	// light setting 
    D3DLIGHT9 lit;
    ::ZeroMemory(&lit, sizeof(lit));
    lit.Type         = D3DLIGHT_POINT;
    lit.Diffuse      = d3d::WHITE; 
	lit.Specular     = d3d::WHITE * 0.9f;
    lit.Ambient      = d3d::WHITE * 0.9f;
    lit.Position     = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
    lit.Range        = 100.0f;
    lit.Attenuation0 = 0.0f;
    lit.Attenuation1 = 0.9f;
    lit.Attenuation2 = 0.0f;
    if (false == g_light.create(Device, lit))
        return false;
	
	// Position and aim the camera.
	D3DXVECTOR3 pos(0.0f, 5.0f, -8.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 2.0f, 0.0f);
	D3DXMatrixLookAtLH(&g_mView, &pos, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &g_mView);
	
	// Set the projection matrix.
	D3DXMatrixPerspectiveFovLH(&g_mProj, D3DX_PI / 4,
        (float)Width / (float)Height, 1.0f, 100.0f);
	Device->SetTransform(D3DTS_PROJECTION, &g_mProj);
	
    // Set render states.
    Device->SetRenderState(D3DRS_LIGHTING, TRUE);
    Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
    Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	
	g_light.setLight(Device, g_mWorld);
	return true;
}

void Cleanup(void)
{
    g_legoPlane.destroy();
	for(int i = 0 ; i < 4; i++) {
		g_legowall[i].destroy();
	}
    destroyAllLegoBlock();
    g_light.destroy();
}


// timeDelta represents the time between the current image frame and the last image frame.
// the distance of moving balls should be "velocity * timeDelta"
bool Display(float timeDelta)  //timeDelta �ʱ�ȭ�� ��� �Ǵ��� ��ã����
{
	int i=0;
	int j = 0;
	
	//timeDelta = 0.001;

	if( Device )
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00afafaf, 1.0f, 0);
		Device->BeginScene();
		
		//������ �Ʒ��� �������� �����̽� �ȴ��� ���·� �����.
		D3DXVECTOR3 coord = g_moving_redball.getCenter();
		if (coord.z <-5.5f) {
			isReset = true;
			D3DXVECTOR3 coord2 = g_target_whiteball.getCenter();
			g_moving_redball.setCenter(coord2.x, (float)M_RADIUS, coord2.z + ((float)M_RADIUS * 2));
			g_moving_redball.setPower(0, 0);
		}

		// update the position of each ball. during update, check whether each ball hit by walls.
		for( i = 0; i < 57; i++) {
			g_sphere[i].ballUpdate(timeDelta);
		}

		g_moving_redball.ballUpdate(timeDelta);
		for (j = 0; j < 4; j++) 
		{
			g_legowall[i].hitBy(g_moving_redball);
		}


		// check whether any two balls hit together and update the direction of balls
		for(i = 0 ;i < 57; i++){
			g_sphere[i].hitBy(g_moving_redball);
		}

		g_target_whiteball.hitBy(g_moving_redball);

		// draw plane, walls, and spheres
		g_legoPlane.draw(Device, g_mWorld);
		for (i=0;i<4;i++) 	{
			g_legowall[i].draw(Device, g_mWorld);
		}
		for (i = 0; i < 57; i++) {
			g_sphere[i].draw(Device, g_mWorld);
		}
		
		g_target_whiteball.draw(Device, g_mWorld);
		g_moving_redball.draw(Device, g_mWorld);
        g_light.draw(Device);
		
		Device->EndScene();
		Device->Present(0, 0, 0, 0);
		Device->SetTexture( 0, NULL );
	}
	return true;
}

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool wire = false;
    static int old_x = 0;
    static int old_y = 0;
    static enum { WORLD_MOVE, LIGHT_MOVE, BLOCK_MOVE } move = WORLD_MOVE;

	
	switch( msg ) {
	case WM_DESTROY:
        {
			::PostQuitMessage(0);
			break;
        }
	case WM_KEYDOWN:
        {
            switch (wParam) {
            case VK_ESCAPE:
				::DestroyWindow(hwnd);
                break;
            case VK_RETURN:
                if (NULL != Device) {
                    wire = !wire;
                    Device->SetRenderState(D3DRS_FILLMODE,
                        (wire ? D3DFILL_WIREFRAME : D3DFILL_SOLID));
                }
                break;
            case VK_SPACE:
				isReset = false;

				D3DXVECTOR3 targetpos = g_target_whiteball.getCenter();
				D3DXVECTOR3	redpos = g_moving_redball.getCenter();
				double theta = acos(sqrt(pow(targetpos.x - redpos.x, 2)) / sqrt(pow(targetpos.x - redpos.x, 2) +
					pow(targetpos.z - redpos.z, 2)));		// �⺻ 1 ��и�
				if (targetpos.z - redpos.z <= 0 && targetpos.x - redpos.x >= 0) { theta = -theta; }	//4 ��и�
				if (targetpos.z - redpos.z >= 0 && targetpos.x - redpos.x <= 0) { theta = PI - theta; } //2 ��и�
				if (targetpos.z - redpos.z <= 0 && targetpos.x - redpos.x <= 0){ theta = PI + theta; } // 3 ��и�
				double distance = sqrt(pow(targetpos.x - redpos.x, 2) + pow(targetpos.z - redpos.z, 2));
				g_moving_redball.setPower(distance * cos(theta), distance * sin(theta));

				
				break;
			}
			break;
        }
		
	case WM_MOUSEMOVE:
        {
            int new_x = LOWORD(lParam);
            int new_y = HIWORD(lParam);
			float dx;
			float dy;
			int x_pos;
          
            if (isReset) {
				// �Ͼ�� ���콺 ���� �����̱�, ù ��� ��ġ�� ������� �� �µ��� �ϰ� �ͱ�� �ѵ� ���� �ذ� ����
				// ���� ������ �� �ʸ� ������ ���콺 Ŀ�� ���� ������ �ϱ�

				dx = (old_x - new_x);
				dy = (old_y - new_y);// * 0.01f;

				D3DXVECTOR3 coord3d = g_target_whiteball.getCenter();
				g_target_whiteball.setCenter((coord3d.x) + (dx*(-0.006f)), coord3d.y, -3.95f);
				g_moving_redball.setCenter((coord3d.x) + (dx*(-0.006f)), coord3d.y, -3.95f+ ((float)M_RADIUS * 2));

				old_x = new_x;
				old_y = new_y;

				move = WORLD_MOVE;

			// world ȸ���ϴ� �κ� �ʿ� ����
             /*     D3DXVECTOR3 vDist;
                    D3DXVECTOR3 vTrans;
                    D3DXMATRIX mTrans;
                    D3DXMATRIX mX;
                    D3DXMATRIX mY;
					
                    switch (move) {
                    case WORLD_MOVE:
                        dx = (old_x - new_x) * 0.01f;
                        dy = (old_y - new_y) * 0.01f;
                        D3DXMatrixRotationY(&mX, dx);
                        D3DXMatrixRotationX(&mY, dy);
                        g_mWorld = g_mWorld * mX * mY;
						
                        break;
                    }*/
                
                old_x = new_x;
                old_y = new_y;

			}
			else { //�����̽� ���� ��

				dx = (old_x - new_x);
				dy = (old_y - new_y);// * 0.01f;

				D3DXVECTOR3 coord3d = g_target_whiteball.getCenter();
				g_target_whiteball.setCenter((coord3d.x) + (dx*(-0.006f)), coord3d.y, -3.95f);

				old_x = new_x;
				old_y = new_y;

				move = WORLD_MOVE;

			}

            break;
        }
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
    srand(static_cast<unsigned int>(time(NULL)));
	
	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
	
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}
	
	// ���⿡ timedelta �ʱ�ȭ�ϰ� 
	// timedelta ���� Display�� call �ϴ°� �ƴұ�???
	//
	d3d::EnterMsgLoop( Display );
	
	Cleanup();
	
	Device->Release();
	
	return 0;
}