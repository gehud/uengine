#include "vector3.h"

namespace ue {
	const vector3 vector3::one		{  1.0f,  1.0f,  1.0f };
	const vector3 vector3::zero		{  0.0f,  0.0f,  0.0f };
	const vector3 vector3::right	{  1.0f,  0.0f,  0.0f };
	const vector3 vector3::left		{ -1.0f,  0.0f,  0.0f };
	const vector3 vector3::up		{  0.0f,  1.0f,  0.0f };
	const vector3 vector3::down		{  0.0f, -1.0f,  0.0f };
	const vector3 vector3::forward	{  0.0f,  0.0f,  1.0f };
	const vector3 vector3::back		{  0.0f,  0.0f, -1.0f };
}