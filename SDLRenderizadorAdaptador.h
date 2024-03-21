#include "RenderDataDTO.h";

class RendererPort
	{
	public:
		virtual void renderElement(const RenderDataDTO& renderDataDTO) = 0;
		virtual ~RendererPort() {}
	};