//#include "Canimation.h"
//
//
//
//
//void CAnimations::Add(int id, LPANIMATION ani)
//{
//	
//	animations[id] = ani;
//
//}
//
//LPANIMATION CAnimations::Get(int id)
//{
//	return animations[id];
//}
//
//CAnimations * CAnimations::GetInstance()
//{
//	if (__instance == NULL) __instance = new CAnimations();
//	return __instance;
//}
//
//void CAnimation::Add(int spriteId, DWORD time)
//{
//	int t = time;
//	if (time == 0) t = this->defaultTime;
//
//	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
//	LPANIMATION_FRAME frame = new CanimationFrame(sprite, t);
//	frames.push_back(frame);
//}
//
//void CAnimation::Render(float x, float y, int alpha)
//{
//	DWORD now = GetTickCount();
//	if (currentFrame == -1)
//	{
//		currentFrame = 0;
//		lastFrameTime = now;
//	}
//	else
//	{
//		DWORD t = frames[currentFrame]->GetTime();
//		if (now - lastFrameTime > t)
//		{
//			currentFrame++;
//			lastFrameTime = now;
//			if (currentFrame == frames.size()) currentFrame = 0;
//		}
//
//	}
//
//	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
//}
//CAnimations * CAnimations::__instance = NULL;
//
