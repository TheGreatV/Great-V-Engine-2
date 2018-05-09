#pragma region Include

#pragma once

#include "Core_1_0.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		class Core_1_2:
			public virtual Core
		{
		protected:
			const PFNGLDRAWRANGEELEMENTSPROC	glDrawRangeElements	 = nullptr;
			const PFNGLTEXIMAGE3DPROC			glTexImage3D		 = nullptr;
			const PFNGLTEXSUBIMAGE3DPROC		glTexSubImage3D		 = nullptr;
			const PFNGLCOPYTEXSUBIMAGE3DPROC	glCopyTexSubImage3D	 = nullptr;
		protected:
			inline Core_1_2() = default;
			inline Core_1_2(
				const PFNGLDRAWRANGEELEMENTSPROC&	glDrawRangeElements_,
				const PFNGLTEXIMAGE3DPROC&			glTexImage3D_,
				const PFNGLTEXSUBIMAGE3DPROC&		glTexSubImage3D_,
				const PFNGLCOPYTEXSUBIMAGE3DPROC&	glCopyTexSubImage3D_
			);
		};
#pragma region Core_1_2
		Core_1_2::Core_1_2(
			const PFNGLDRAWRANGEELEMENTSPROC&	glDrawRangeElements_,
			const PFNGLTEXIMAGE3DPROC&			glTexImage3D_,
			const PFNGLTEXSUBIMAGE3DPROC&		glTexSubImage3D_,
			const PFNGLCOPYTEXSUBIMAGE3DPROC&	glCopyTexSubImage3D_
		):
			glDrawRangeElements		(glDrawRangeElements_	),
			glTexImage3D			(glTexImage3D_			),
			glTexSubImage3D			(glTexSubImage3D_		),
			glCopyTexSubImage3D		(glCopyTexSubImage3D_	)
		{
		}
#pragma endregion

		class Context_1_2:
			public Context_1_0,
			public virtual Core_1_2
		{
		};
#pragma region Context_1_2
#pragma endregion

		namespace OSs
		{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
			namespace Windows
			{
				class Context_1_2:
					public Context_1_0,
					protected OpenGL::Context_1_2
				{
				private:
					inline static Attributes GetAttributes();
				private:
					inline Context_1_2(const Handle& handle_);
				protected:
					inline Context_1_2(const Handle& handle_, const EmptyTag&);
				public:
					inline Context_1_2(const DeviceContextHandle& deviceContextHandle_);
				};
#pragma region Context_1_2
				Context_1_2::Attributes Context_1_2::GetAttributes()
				{
					return{
						WGL_CONTEXT_MAJOR_VERSION_ARB, 1,
						WGL_CONTEXT_MINOR_VERSION_ARB, 2,
						WGL_CONTEXT_FLAGS_ARB, 0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
						0, 0,
					};
				}

				Context_1_2::Context_1_2(const Handle& handle_):
					Windows::Context_1_0(handle_),		// TODO: need to call this before GetProcedureAddress in Core_1_2 constructor
					OpenGL::Context_1_2(),
					Core_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D, handle_)
					)
				{
						MakeCurrent(nullptr, nullptr);
					}
				Context_1_2::Context_1_2(const Handle& handle_, const EmptyTag&):
					Windows::Context_1_0(handle_),
					OpenGL::Context_1_2(),
					Core_1_2()
				{
					}
				Context_1_2::Context_1_2(const DeviceContextHandle& deviceContextHandle_):
					Context_1_2(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
				{
				}
#pragma endregion
			}
#endif
		}
	}
}


#pragma region
#pragma endregion


