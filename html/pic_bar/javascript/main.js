$(document).ready(function(){
	
	$('.main_pic').mouseenter(function(){
		$('.zoom_pic').css('display', 'block');
		$('.scale_frame').css('display', 'block');
	});

	$('.main_pic').mouseleave(function(){
		$('.zoom_pic').css('display', 'none');
		$('.scale_frame').css('display', 'none');
	});

	$('.main_pic').mousemove(function(event) {
		if ( $('.zoom_pic').css('display') != 'block' ) {
			return;
		}

		$('.zoom_pic img').css('top', '-'+event.pageY+'px');
		$('.zoom_pic img').css('left', '-'+event.pageX+'px');

		$('.scale_frame').css('top', event.pageY-350-75+'px');
		$('.scale_frame').css('left', event.pageX-75+'px');
	});


	$('.pic_list li').mouseover(function(){
		$(this).siblings().removeClass('pic_list_hover');
		$(this).addClass('pic_list_hover');


        $('.main_pic img').attr('src', ('image/pic'+($(this).index()+1)+'.jpg'));
		$('.zoom_pic img').attr('src', 'image/zoom_pic'+($(this).index()+1)+'.jpg');
	});
});
