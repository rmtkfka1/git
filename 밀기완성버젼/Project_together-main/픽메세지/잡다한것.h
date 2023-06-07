#pragma once

// 서성규
// ===================================================================================
// 위쪽
		
		/*Pos RenderPosP2 = _posP2 - _DiffP1;
		TransparentBlt(mdc, _RenderPosP1.x, WINDOW_HEIGHT / 2 - _RenderPosP1.y * 0.25, size.x, size.y,
			mdcP1, 0, 0, size.x, size.y, RGB(0, 0, 0));

		TransparentBlt(mdc, RenderPosP2.x, WINDOW_HEIGHT / 2 - _RenderPosP2.y * 0.25, size.x, size.y,
			mdcP2, 0, 0, size.x, size.y, RGB(0, 0, 0));*/
		

		// 아래쪽
		/*{
			Pos RenderPosP1 = _posP1 - _DiffP2;

			TransparentBlt(mdc, RenderPosP1.x, RenderPosP1.y * 1.25, size.x, size.y,
				mdcP1, 0, 0, size.x, size.y, RGB(0, 0, 0));

			TransparentBlt(mdc, _RenderPosP2.x, _RenderPosP2.y * 1.25, size.x, size.y,
				mdcP2, 0, 0, size.x, size.y, RGB(0, 0, 0));
		}*/

		/*else if (_DiffP1.x > background->background_img.GetWidth() - WINDOW_WIDTH)
				_DiffP1.x = background->background_img.GetWidth() - WINDOW_WIDTH;*/

				/*else if (_DiffP1.y > 0)
					_DiffP1.y = 0;*/

					/*else if (_DiffP2.x > background->background_img.GetWidth() - WINDOW_WIDTH)
						_DiffP2.x = background->background_img.GetWidth() - WINDOW_WIDTH;*/



						/*else if (_posP1.x > background->background_img.GetWidth() - WINDOW_WIDTH / 2)
							_RenderPosP1.x -= _stat.speed * deletaTime;*/

							//else if (_posP1.x > background->background_img.GetWidth() - WINDOW_WIDTH / 2)
							//	_RenderPosP1.x += _stat.speed * deletaTime;










////상혁//////////////////////////////////////////////
// player 220 라인 중력부분 수정해야됨
// 점프씹히는거 수정해야됨
