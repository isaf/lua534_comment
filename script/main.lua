function bar()
	print('bar');
	print(2222222, coroutine.yield(3, 4, 5));
	print(44444, 'end bar')
end;

function foo()
	print('start foo')
	local co = coroutine.create(bar);
	print(33333, coroutine.resume(co));
	print(5555555, coroutine.resume(co, 8, 9, 7));
	print('end foo')
end;