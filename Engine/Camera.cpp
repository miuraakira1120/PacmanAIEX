#include "camera.h"
#include "Direct3D.h"

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 20, 0);	//�J�����̈ʒu
	_target = XMFLOAT3( 0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	//�r���[�s��
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), XMVectorSet(0, 1, 0, 0));
}

//�œ_��ݒ�
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }

//�ʒu��ݒ�
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

//�œ_���擾
XMFLOAT3 Camera::GetTarget() { return _target; }

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() { return _position; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }