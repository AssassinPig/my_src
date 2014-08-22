$(document).ready(function(){
	$('.right_bar_list li div').each(function(i, elem){

		elem.onclick = function(){
			$(this).parent().siblings().children().css('top', '-11px');

			if($(elem).css('top') == '0px') {
				$(elem).css('top', '-11px');
			} else {
				$(elem).css('top', '0px');
			}

		}

		if (i==0) {
			$(elem).css('top', '0px');
		}
	});
	
});
